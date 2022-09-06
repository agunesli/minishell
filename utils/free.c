/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:23:26 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 20:23:39 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(char **bin)
{
	int	i;

	i = -1;
	if (!bin)
		return ;
	while (bin[++i])
		free(bin[i]);
	free(bin);
}

void	free_tab3(char ***bin)
{
	int	i;

	i = -1;
	if (!bin)
		return ;
	while (bin[++i])
		free_all(bin[i]);
	free(bin);
}

void	free_tree(t_syntax **syn)
{
	t_syntax	*tmp1;
	t_syntax	*tmp2;

	if (!*syn)
		return ;
	if ((*syn)->content)
	{
		free((*syn)->content);
		(*syn)->content = NULL;
	}
	if ((*syn)->cmd_arg)
	{
		free_all((*syn)->cmd_arg);
		(*syn)->cmd_arg = NULL;
	}
	tmp1 = (*syn)->left;
	tmp2 = (*syn)->right;
	free(*syn);
	*syn = NULL;
	free_tree(&tmp1);
	free_tree(&tmp2);
}

void	ft_free_end(t_data *my_data)
{
	if (my_data->syn)
		free_tree(&my_data->syn);
	if (my_data->childs)
	{
		free(my_data->childs);
		my_data->childs = NULL;
	}
	if (my_data->all_cmd)
	{
		free_tab3(my_data->all_cmd);
		my_data->all_cmd = NULL;
	}
	free_all(my_data->env);
	free_all(my_data->exprt);
	free(my_data->path);
}

void	ft_free_necessary(t_data *my_data)
{
	if (my_data->syn)
	{
		free_tree(&my_data->syn);
	}
	if (my_data->childs)
	{
		free(my_data->childs);
		my_data->childs = NULL;
	}
	if (my_data->all_cmd)
	{
		free_tab3(my_data->all_cmd);
		my_data->all_cmd = NULL;
	}
}

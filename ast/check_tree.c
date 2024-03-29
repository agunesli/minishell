/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:29:12 by agunesli          #+#    #+#             */
/*   Updated: 2022/08/31 18:29:30 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_strong(t_syntax *syn, t_data *my_data)
{
	if (syn->left == NULL)
	{
		if (syn->id == OR)
			return (error_syntax("\'||\'", my_data));
		else if (syn->id == AND)
			return (error_syntax("\'&&\'", my_data));
		else if (syn->id == PIPE)
			return (error_syntax("\'|\'", my_data));
	}
	if (syn->right == NULL)
		write_more(syn, my_data);
}

void	check_medium(t_syntax *syn, t_data *my_data)
{
	if (syn->left != NULL && in <= syn->left->id && syn->left->id <= append)
	{
		if (syn->left->id == in)
			return (error_syntax("\'<\'", my_data));
		if (syn->left->id == out)
			return (error_syntax("\'>\'", my_data));
		if (syn->left->id == heredoc)
			return (error_syntax("\'<<\'", my_data));
		if (syn->left->id == append)
			return (error_syntax("\'>>\'", my_data));
	}
	if (!syn->content)
		return (error_syntax("\'newline\'", my_data));
	else if (syn->content && syn->id != heredoc)
		check_open(syn->content, syn->id, my_data);
}

void	check_tree(t_syntax *syn, t_data *my_data)
{
	if (!syn)
		return ;
	if (syn->id == PIPE || syn->id == AND || syn->id == OR)
		check_strong(syn, my_data);
	else if (in <= syn->id && syn->id <= append)
		check_medium(syn, my_data);
	if (!my_data->syntax)
		return ;
	check_tree(syn->left, my_data);
	check_tree(syn->right, my_data);
}

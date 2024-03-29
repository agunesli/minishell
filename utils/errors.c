/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:24:02 by tamather          #+#    #+#             */
/*   Updated: 2022/09/07 01:29:48 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	putstr_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	errorp(char *str, t_data *my_data)
{
	g_error = errno;
	putstr_error("bash: ");
	putstr_error(str);
	perror(" ");
	ft_free_necessary(my_data);
}

void	error_syntax(char *str, t_data *my_data)
{
	g_error = 2;
	my_data->syntax = 0;
	putstr_error("bash: syntax error near unexpected token ");
	putstr_error(str);
	putstr_error("\n");
	free_tree(&my_data->syn);
}

void	error_command(char *str, t_data *my_data)
{
	g_error = 127;
	putstr_error("bash: ");
	putstr_error(str);
	putstr_error(": command not found\n");
	free_all(my_data->env);
	ft_free_necessary(my_data);
	exit(127);
}

int	error_invalid_id(char *str)
{
	g_error = 1;
	putstr_error("bash: export: '");
	putstr_error(str);
	putstr_error("' : not a valid identifier\n");
	return (1);
}

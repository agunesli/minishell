/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:52:39 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 20:52:40 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_fd(int ft_init[2])
{
	dup2(ft_init[0], STDIN_FILENO);
	close(ft_init[0]);
	dup2(ft_init[1], STDOUT_FILENO);
	close(ft_init[1]);
}

void	exec_one_cmd(t_data *my_data, t_syntax *syn)
{
	int	status;

	if (!my_data->all_cmd[my_data->crt]
		|| !my_data->all_cmd[my_data->crt][0])
		return ;
	status = is_builtins(my_data);
	if (status)
	{
		change_fd(my_data->syn, my_data);
		g_error = hub_builtins(status, my_data);
		ft_free_necessary(my_data);
	}
	else
	{
		update_data_exec(my_data);
		exec(syn, my_data);
		end_of_parent(my_data);
	}
}

void	get_start_exec(t_data *my_data, t_syntax *syn)
{
	int	fd_sdt[2];

	fd_sdt[0] = dup(STDIN_FILENO);
	fd_sdt[1] = dup(STDOUT_FILENO);
	if (syn->id >= in)
		exec_one_cmd(my_data, syn);
	else
		exec_with_pipe(my_data, syn);
	clean_fd(fd_sdt);
}

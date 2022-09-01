/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:51:22 by agunesli          #+#    #+#             */
/*   Updated: 2022/08/30 13:01:13 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_data_exec(t_data *my_data)
{
	if (my_data->nb_process != 1)
	{
//		my_data->fd = malloc(sizeof(int) * 3);
//		if (!my_data->fd)
//			return ; //Error malloc
		if (pipe(my_data->fd[0]) == -1)
			printf("Error\n");
		if (pipe(my_data->fd[1]) == -1)
			printf("Error\n");
	}
	my_data->childs = malloc(sizeof(int) * my_data->nb_process);
	if (!my_data->childs)
		return ;// Error malloc
}

//fork() => child process = 0 else main process
//pipe() => fd[0] = read (in), fd[1] = write (out)
//execve => v = array, e = env (Error = -1)
void	exec(t_syntax *syn, t_data *my_data)
{
	char	*path;
	int		built;

//	change_pipe(my_data);
	my_data->childs[my_data->crt] = fork();
//	if (my_data->childs[my_data->current_process] == -1)
//		printf("Fail to create a new process\n");
	if (my_data->childs[my_data->crt] == 0)
	{
		signal(SIGQUIT, signal_ctrbs);
		good_fd(syn, my_data);
		built = is_builtins(my_data);
		if (built)
			exit(hub_builtins(built, my_data));
		path = correct_path(my_data->all_cmd[my_data->crt], my_data);
	//	print_all(my_data->all_cmd[my_data->crt]);
		if (path && execve(path, my_data->all_cmd[my_data->crt], my_data->env) == -1)
		{
			g_error = errno;
			errorp(path);
		}
		exit(0);
	}
	else
		signal(SIGINT, SIG_IGN);
	my_data->crt++;
}

void	end_of_parent(t_data *my_data)
{
	int	i;
	int	status;

	i = -1;

	close(my_data->fd[0][0]);
	close(my_data->fd[0][1]);
	close(my_data->fd[1][0]);
	close(my_data->fd[1][1]);
//	close(my_data->fd[0]);
//	close(my_data->fd[1]);
//	close(my_data->fd[2]);
	while (++i < my_data->nb_process)
	{
		waitpid(my_data->childs[i], &status, 0);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_error = WTERMSIG(status);
	}
	free(my_data->childs);
}

void	exec_with_pipe(t_data *my_data, t_syntax *syn)
{

	update_data_exec(my_data);
	while (syn && syn->id < in && syn->left)
	{
		exec(syn->left, my_data);
		syn = syn->right;
	}
	exec(syn, my_data);
	end_of_parent(my_data);
}

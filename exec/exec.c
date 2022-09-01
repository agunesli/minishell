/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:51:22 by agunesli          #+#    #+#             */
/*   Updated: 2022/09/01 22:18:20 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_data_exec(t_data *my_data)
{
//	if (my_data->nb_process != 1)
//	{
//		my_data->fd = malloc(sizeof(int) * 3);
//		if (!my_data->fd)
//			return ; //Error malloc
//		if (pipe(my_data->fd[0]) == -1)
//			printf("Error\n");
	//	if (pipe(my_data->fd[1]) == -1)
	//		printf("Error\n");
//	}
	my_data->fd_tmp = STDIN_FILENO;
	my_data->childs = malloc(sizeof(int) * my_data->nb_process);
	if (!my_data->childs)
		return ;// Error malloc
}

void	ft_dup2(int fd[2], t_data *my_data)
{
	if (my_data->crt != 0)
	{
		dup2(my_data->fd_tmp, STDIN_FILENO);
	//	close(my_data->fd_tmp);
	}
	if (my_data->crt != my_data->nb_process - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
	//	close(fd[1]);
		close(fd[0]);
	}
}

//fork() => child process = 0 else main process
//pipe() => fd[0] = read (in), fd[1] = write (out)
//execve => v = array, e = env (Error = -1)
void	exec(t_syntax *syn, t_data *my_data)
{
	char	*path;
	int		built;
	int		fd[2];

	if (my_data->crt != my_data->nb_process - 1)
		pipe(fd);
	else
		fd[1] =  STDOUT_FILENO;
	my_data->childs[my_data->crt] = fork();
//	if (my_data->childs[my_data->current_process] == -1)
//		printf("Fail to create a new process\n");
	if (my_data->childs[my_data->crt] == 0) //enfant
	{
		signal(SIGQUIT, signal_ctrbs);
		ft_dup2(fd, my_data);
		change_fd(syn);
		built = is_builtins(my_data);
		if (built)
			exit(hub_builtins(built, my_data));
		path = correct_path(my_data->all_cmd[my_data->crt], my_data);
		if (path && execve(path, my_data->all_cmd[my_data->crt], my_data->env) == -1)
		{
			g_error = errno;
			errorp(path);
		}
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
	if (my_data->fd_tmp != STDIN_FILENO)
		close(my_data->fd_tmp);
	my_data->fd_tmp = fd[0];
	my_data->crt++;
}

void	end_of_parent(t_data *my_data)
{
	int	i;
	int	status;

	i = -1;

//	close(my_data->fd[0][0]);
//	close(my_data->fd[0][1]);
//	close(my_data->fd[1][0]);
//	close(my_data->fd[1][1]);
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

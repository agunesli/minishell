/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:51:22 by agunesli          #+#    #+#             */
/*   Updated: 2022/07/21 13:56:50 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtins(t_data *my_data)
{
	if (!ft_strncmp("echo", my_data->all_cmd[0][0], ft_strlen("echo") + 1))
		return (ft_echo(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("pwd", my_data->all_cmd[0][0], ft_strlen("pwd") + 1))
		return (ft_pwd(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("cd", my_data->all_cmd[0][0], ft_strlen("cd") + 1))
		return (ft_cd(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("exit", my_data->all_cmd[0][0], ft_strlen("exit") + 1))
		return (ft_exit(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("export", my_data->all_cmd[0][0], ft_strlen("export") + 1))
		return (ft_export(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("unset", my_data->all_cmd[0][0], ft_strlen("unset") + 1))
		return (ft_unset(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("env", my_data->all_cmd[0][0], ft_strlen("env") + 1))
		return (ft_env(my_data->all_cmd[my_data->crt], my_data));
	return(-1);
}

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
void	exec(t_syntax *syn, t_data *my_data)
{
	char	*path;
	int		status;

	if (is_builtins(my_data) != -1)
	{
		my_data->crt++;
		return ;
	}
	my_data->childs[my_data->crt] = fork();
//	if (my_data->childs[my_data->current_process] == -1)
//		Error;
	if (my_data->childs[my_data->crt] == 0)
	{
		good_fd(syn, my_data);
		path = correct_path(my_data->all_cmd[my_data->crt], my_data);
		dprintf(2, "%s\n", path);
		print_all(my_data->all_cmd[my_data->crt]);
		status = execve(path, my_data->all_cmd[my_data->crt], my_data->env);
		if (status == -1)
			perror("");
	}
	my_data->crt++;
}

void	update_data_exec(t_data *my_data)
{
	if (pipe(my_data->fd[0]) == -1)
		printf("Error\n");
	if (pipe(my_data->fd[1]) == -1)
		printf("Error\n");
	my_data->childs = malloc(sizeof(int) * my_data->nb_process);
	if (!my_data->childs)
		return ; // Error malloc
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
	while (++i < my_data->nb_process)
	{
		status = waitpid(my_data->childs[i], NULL, 0);
		if (!status)
		{
			my_data->status_error = status;
			perror("");
		}
	}
	free(my_data->childs);
}

void	start_exec(t_data *my_data, t_syntax *syn)
{
	t_syntax	*next;

	update_data_exec(my_data);
	if (syn->id >= in)
	{
		exec(syn, my_data);
		end_of_parent(my_data);
		return ;
	}
	else
		exec(syn->left, my_data);
	while (syn && syn->id < in)
	{
		if (!syn->right->left)
			break ;
		next = syn->right->left;
		exec(next, my_data);
		syn = syn->right;
	}
	exec(syn->right, my_data);
	end_of_parent(my_data);
}

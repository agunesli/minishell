/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:34:25 by agunesli          #+#    #+#             */
/*   Updated: 2022/07/18 15:45:54 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
void	exec(t_syntax *syn, t_data *my_data)
{
	char	*path;
	int		status;

	my_data->childs[current_process] = fork();
//	if (my_data->childs[current_process] == -1)
//		Error;
	if (my_data->childs[current_process] == 0)
	{
		good_fd(syn, data);
		path = correct_path(my_data->all_cmd, my_data);
		status = execve(path, my_data->all_cmd[current_process], my_data->env);
		//if (status == -1)
			//Error
	}
}

/*void	exec(t_data my_data)
{
//	int fds[2][2];
//	int	*childs;

	if (pipe(my_data->fds[0]) == -1)
		printf("Error\n");
	if (pipe(my_data->fds[1]) == -1)
		printf("Error\n");
	my_data->childs = malloc(sizeof(int) * my_data->nb_process);
	if (!my_data->childs)
		return (NULL);

}*/

void	hub_strong(int id, t_syntax *syn, t_data *my_data)
{
	int	status_wait;

	if (nb_process > 0 && id != PIPE)
		status_wait = waitpid(childs[current_process - 1], NULL, 0);
	if (id == PIPE)
		childs[current_process] = exec(syn, my_data);
	else if (id == AND && status_wait == 0)
		childs[current_process] = exec(syn, my_data);
	else if (id == OR && status_wait != 0)
		childs[current_process] = exec(syn, my_data);
	if (!status_wait)
		errorp
}

void	start_exec(t_data *my_data, t_syntax *syn)
{
	t_syntax	*next;

	if (syn->id > in)
	{
		exec(syn, my_data);
		return ;
	}
	else
		exec(syn->left, my_data);
	while (syn && syn-> id < in)
	{
		if (!syn->right->left)
			return ;
		next = syn->right->left;
		hub_strong(syn->id, next, my_data);
		syn = syn->right;
	}
	hub_string(syn->id, syn->right, my_data);
}

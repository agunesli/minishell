#include "../minishell.h"

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
void	exec(t_syntax *syn, t_data *my_data)
{
	char	*path;
	int		status;

	printf("%d\n",my_data->current_process); //
	print_all(my_data->all_cmd[my_data->current_process]); //
	my_data->childs[my_data->current_process] = fork();
//	if (my_data->childs[my_data->current_process] == -1)
//		Error;
	if (my_data->childs[my_data->current_process] == 0)
	{
		good_fd(syn, my_data);
		path = correct_path(my_data->all_cmd[my_data->current_process], my_data);
		dprintf(2, "path is %s\n", path);
		status = execve(path, my_data->all_cmd[my_data->current_process], my_data->env);
		if (status == -1)
			perror("");
	}
	my_data->current_process++;
}

void	update_data_exec(t_data *my_data)
{
//	int fds[2][2];
//	int	*childs;

	if (pipe(my_data->fd[0]) == -1)
		printf("Error\n");
	if (pipe(my_data->fd[1]) == -1)
		printf("Error\n");
	my_data->childs = malloc(sizeof(int) * my_data->nb_process);
	if (!my_data->childs)
		return ; // Error malloc
}

void	hub_strong(int id, t_syntax *syn, t_data *my_data)
{
	int	status_wait;

	dprintf(2, "id is %d\n", id);
	if (my_data->nb_process > 0 && id != PIPE)
		status_wait = waitpid(my_data->childs[my_data->current_process - 1], NULL, 0);
	else
		status_wait = 0;
	dprintf(2,"BOUHH %d\n", syn->id);
	if (id == PIPE)
		exec(syn, my_data);
	else if (id == AND && status_wait == 0)
		exec(syn, my_data);
	else if (id == OR && status_wait != 0)
		exec(syn, my_data);
	if (status_wait)
		dprintf(2,"here\n");
//		perror("");
}

void	end_of_parent(t_data *my_data)
{
	int	i;
	int	status;

	i = -1;
	close(my_data->fd[0][0]);
	close(my_data->fd[1][0]);
	close(my_data->fd[0][1]);
	close(my_data->fd[1][1]);
	while (++i< my_data->nb_process)
	{
		status = waitpid(my_data->childs[i], NULL, 0);
		if (!status)
			perror("");
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
		return ;
	}
	else
		exec(syn->left, my_data);
	while (syn && syn->id < in)
	{
		if (!syn->right->left)
			break ;
		next = syn->right->left;
		hub_strong(syn->id, next, my_data);
		syn = syn->right;
	}
	hub_strong(syn->id, syn->right, my_data);
	end_of_parent(my_data);
}

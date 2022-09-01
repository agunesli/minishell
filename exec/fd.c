#include "../minishell.h"

void	change_fd(t_syntax *syn)
{
	int	fd;

	if (!syn)
		return ;
	if (syn->id == in || syn->id == heredoc)
	{
		fd = open_file(syn->content, syn->id);
		dup2(fd, STDIN_FILENO);
		close(fd);
		change_fd(syn->right);
	}
	else if (syn->id == out || syn->id == append)
	{
		fd = open_file(syn->content, syn->id);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		change_fd(syn->right);
	}
}

/*void	change_pipe(t_data *my_data)
{
	printf("the current process is %d\n", my_data->crt);
	if (my_data->crt != 0)
		my_data->fd[2] = my_data->fd[0];
	else
		my_data->fd[2] = -1;
	pipe(my_data->fd);
	printf("fds is %d %d %d \n", my_data->fd[0], my_data->fd[1], my_data->fd[2]);
}*/

// MARCHE PAS CAR BOUCLE INFINI FAIRE LA TECHNIQUE D'ADRIEN !!!!
// fd => fd[0] in actuel fd[1] out actuel fd[2] in futur (technique adrien)
// fd => fd[0] in futur fd[1] out actuel fd[2] in actuel
// la technique de Lylian faire une recursive ! (je prefere celle la !)
/*void	good_fd(t_syntax *syn, t_data *my_data)
{
	close(my_data->fd[0]);
	if (my_data->crt != 0)
		dup2(my_data->fd[2], STDIN_FILENO);
//	close(my_data->fd[2]);
	if (my_data->crt != my_data->nb_process - 1)
		dup2(my_data->fd[1], STDOUT_FILENO);
//	close(my_data->fd[1]);
//	printf(":crt is %d [%d] and nb process is %d\n", my_data->crt, my_data->crt%2, my_data->nb_process);
	close(my_data->fd[my_data->crt % 2][1]);
	close(my_data->fd[(my_data->crt + 1) % 2][0]);
	if (my_data->crt != 0)
	{
		printf("in %d\n",(my_data->crt) % 2);
		dup2(my_data->fd[my_data->crt % 2][0], STDIN_FILENO);
	}
//	close(my_data->fd[my_data->crt % 2][0]);
	if (my_data->crt != my_data->nb_process - 1)
	{
		printf("out %d\n",(my_data->crt + 1) % 2);
		dup2(my_data->fd[(my_data->crt + 1) % 2][1], STDOUT_FILENO);
	}
//	close(my_data->fd[(my_data->crt + 1) % 2][1]);
	change_fd(syn);
}*/

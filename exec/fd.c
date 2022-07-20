#include "../minishell.h"

void	change_fd(t_syntax *syn)
{
	int	fd;

	if (!syn)
		return ;
	if (syn->id == in || syn->id == heredoc)
	{
		fd = open_file(syn->content, syn->id);
		dup2(fd, STDIN_FILENO); //check error ?
		close(fd);
		change_fd(syn->right);
	}
	else if (syn->id == out || syn->id == append)
	{
		fd = open_file(syn->content, syn->id);
		dup2(fd, STDOUT_FILENO); //check error ?
		close(fd);
		change_fd(syn->right);
	}
}

void	good_fd(t_syntax *syn, t_data *my_data)
{
	close(my_data->fd[(my_data->crt + 1) % 2][0]);
	close(my_data->fd[my_data->crt % 2][1]);
	if (my_data->crt != 0)
		dup2(my_data->fd[my_data->crt % 2][0], STDIN_FILENO);
	close(my_data->fd[my_data->crt % 2][0]);
	if (my_data->crt != my_data->nb_process - 1)
		dup2(my_data->fd[(my_data->crt + 1) % 2][1], STDOUT_FILENO);
	close(my_data->fd[(my_data->crt + 1) % 2][1]);
	change_fd(syn);
}

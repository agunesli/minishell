#include "../minishell.h"

void	change_fd(t_syntax *syn, int fd_in, int fd_out)
{
	int	fd;

	if (!syn)
		return ;
	if (syn->id == in || syn->id == heredoc)
	{
		fd = open_file(syn->content, syn->id);
		dprintf(2,"IN : fd is %d and name file is %s\n", fd, syn->content);//
		dup2(fd, fd_in); //check error ?
		close(fd);
		change_fd(syn->right, fd, fd_out);
	}
	else if (syn->id == out || syn->id == append)
	{
		fd = open_file(syn->content, syn->id);
		dprintf(2,"OUT : fd is %d and name file is %s\n", fd, syn->content); //
		dup2(fd, fd_out); //check error ?
		close(fd);
		change_fd(syn->right, fd_in, fd);
	}
}

void	good_fd(t_syntax *syn, t_data *data)
{
	change_fd(syn, STDIN_FILENO, STDOUT_FILENO);
	close(my_data->fd[(current_process + 1)%2][0]);
	close(my_data->fd[current_process%2][1]);
	if (my_data->current_process != 0)
	{
		dup2(my_data->fd[current_process%2][0], STDIN_FILENO);
		close(my_data->fd[current_process%2][0]);
	}
	if (my_data->current_process != my_data->nb_process - 1)
	{
		dup2(my_data->fd[(current_process + 1)%2][1], STDOUT_FILENO);
		close(my_data->fd[(current_process + 1)%2][1]);
	}
}
/*
void	change_all_fd(t_syntax *syn)
{
	while (syn && syn->id < in)
	{
		change_fd(syn->left, STDIN_FILENO, STDOUT_FILENO);
		dprintf(2,"\n");
		syn = syn->right;
	}
	change_fd(syn, STDIN_FILENO, STDOUT_FILENO);
}*/

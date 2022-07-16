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

void	change_all_fd(t_syntax *syn)
{
	while (syn && syn->id < in)
	{
		change_fd(syn->left, STDIN_FILENO, STDOUT_FILENO);
		dprintf(2,"\n");
		syn = syn->right;
	}
	change_fd(syn, STDIN_FILENO, STDOUT_FILENO);
}

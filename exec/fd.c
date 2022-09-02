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

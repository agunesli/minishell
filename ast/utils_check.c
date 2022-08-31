#include "../minishell.h"

char	*without_nl(char *src)
{
	char	*dest;

	dest = ft_substr(src, 0, ft_strlen(src) - 1);
	free(src);
	return (dest);
}

void	write_more(t_syntax *syn, t_data *my_data)
{
	char	*line;
	int		b;

	b = dup(STDIN_FILENO);
	signal(SIGINT, sg_heredoc);
//	signal(SIGINT, SIG_DFL);
	line = readline("> ");
	printf("line is %s\n", line);
	if (!line && g_error != 666)
	{
		printf("bash: syntax error: unexpected end of file\nexit");
		free_tree(my_data->syn);
		exit(2);
	}
	if (line && *line)
		syn->right = strong_piece(line, my_data);
	else
	{
		syn->right = NULL;
		my_data->syntax = 0;
	}
	dup2(b, STDIN_FILENO);
	signal_def();
}

void	check_open(char *name, int opt, t_data *my_data)
{
	int	fd;

	fd = open_file(name, opt);
	if (fd == -1)
		my_data->syntax = 0;
	close(fd);
}

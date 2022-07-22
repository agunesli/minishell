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

	write(1, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (!ft_strncmp(line, "\n", 1))
	{
		free(line);
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	line = without_nl(line);
	syn->right = strong_piece(line, my_data);
}

void	check_open(char *name, int opt)
{
	int	fd;

	fd = open_file(name, opt);
	close(fd);
}

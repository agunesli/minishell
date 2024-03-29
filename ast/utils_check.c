/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:25:52 by agunesli          #+#    #+#             */
/*   Updated: 2022/09/07 09:05:22 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	line = readline("> ");
	if (!line && g_error != 130)
	{
		printf("bash: syntax error: unexpected end of file\nexit");
		free_tree(&my_data->syn);
		exit(2);
	}
	if (line && *line)
		syn->right = strong_piece(line, my_data);
	else
	{
		syn->right = NULL;
		my_data->syntax = 0;
		error_syntax("|", my_data);
	}
	dup2(b, STDIN_FILENO);
	close(b);
	signal_def();
}

void	check_open(char *name, int opt, t_data *my_data)
{
	int	fd;

	fd = open_file(name, opt, my_data);
	if (fd == -1)
		my_data->syntax = 0;
	else
		close(fd);
}

char	*found_name_fd(char *subread, int y)
{
	int	i;

	i = 0;
	while (subread[y] == ' ')
		y++;
	i = y;
	while (subread[y] && subread[y] != ' ' && subread[y] != '\n'
		&& subread[y] != '>' && subread[y] != '<')
		y++;
	return (ft_substr(subread, i, y - i));
}

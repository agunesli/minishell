/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:26:10 by agunesli          #+#    #+#             */
/*   Updated: 2022/09/01 18:02:17 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*found_limiter(char *subread, int y, t_data *my_data)
{
	int		len;

	len = 0;
	if (!subread[y])
	{
		error_syntax("\'newline\'", my_data);
		return (NULL);
	}
	else if (subread[y] == '<')
	{
		error_syntax("\'<<\'", my_data);
		return (NULL);
	}
	while (subread[len + y] && (!ft_is_in_set(subread[len + y], MEDIUM)
			&& subread[len + y] != ' '))
		len++;
	return (ft_substr(subread, y, len));
}

char	*found_name_fd_heredoc(void)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	int		fd;

	i = 0;
	tmp1 = ft_itoa(i);
	tmp2 = ft_strjoin("/tmp/.here_doc", tmp1);
	fd = open(tmp2, O_WRONLY, 0777);
	while (++i && fd != -1)
	{
		free(tmp1);
		free(tmp2);
		tmp1 = ft_itoa(i);
		tmp2 = ft_strjoin("/tmp/.here_doc", tmp1);
		close(fd);
		fd = open(tmp2, O_WRONLY, 0777);
	}
	free(tmp1);
	close(fd);
	return (tmp2);
}

char	*expand_heredoc(char *line, t_data *my_data)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
			return (expand_heredoc(change_expand(line, i, my_data), my_data));
	}
	return (line);
}

void	write_heredoc(int fd, char *lim, t_data *my_data)
{
	char	*line;
	int		expd;
	int		b;

	signal(SIGINT, sg_heredoc);
	b = dup(STDIN_FILENO);
	expd = 1;
	if (lim[0] == '\"' || lim [0] == '\'')
		lim = ((expd = 0, without_quote(lim)));
	line = readline("> ");
	while (line && ft_strncmp(lim, line, ft_strlen(lim)))
	{
		if (expd)
			line = expand_heredoc(line, my_data);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (g_error == 130)
		my_data->syntax = 0;
	dup2(b, STDIN_FILENO);
	close(b);
	free(line);
	free(lim);
	signal_def();
}

char	*create_heredoc(char *subread, int y, t_data *my_data)
{
	char	*lim;
	char	*name_fd;
	int		fd;
	int		tmp;

	tmp = g_error;
	g_error = 0;
	while (subread[y] == ' ')
		y++;
	lim = found_limiter(subread, y, my_data);
	if (!lim)
		return (NULL);
	name_fd = found_name_fd_heredoc();
	fd = open(name_fd, O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		perror("");
	write_heredoc(fd, lim, my_data);
	close(fd);
	if (g_error == 0)
		g_error = tmp;
	return (name_fd);
}

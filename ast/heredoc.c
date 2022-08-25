#include "../minishell.h"
/* Cette technique d'affichage ne fonctionne pas a revoir !!!
void	error_limiter(char *str, void i, int op, char *subread)
{
	free(subread);
	if (op == 1)
		printf(str, (char)i);
	else
		printf(str, (char *)i);
	exit(0); //a verifier si on doit faire un exit
}

//1 => char 2 => char *
void	check_error_limiter(char *subread, char *read)
{
	int	len;

	len = ft_strlen(subread);
	status_error = 1;
	if (*(read + len) == '\n')
		error_limiter("zsh: parse error near '%c'\n", '\n', 1, subread);
	else if (*(read + len) == '|' && *(read + len + 1) == '|')
		error_limiter("zsh: parse error near '%s'\n", "||", 2, subread);
	else if (*(read + len) == '|' && *(read + len + 1) != '|')
		error_limiter("zsh: parse error near '%c'\n", '|', 1, subread);
	else if (*(read + len) == '&' && *(read + len + 1) == '&')
		error_limiter("zsh: parse error near '%s'\n", "&&", 2, subread);
	else if (*(read + len) == '&' && *(read + len + 1) != '&')
		error_limiter("zsh: parse error near '%c'\n", '&', 1, subread);
	else if (*(read + len) == '<' && *(read + len + 1) == '<')
		error_limiter("zsh: parse error near '%c'\n", '<', 1, subread);
	else if (*(read + len) == '<' && *(read + len + 1) == '\n')
		error_limiter("zsh: parse error near '%c'\n", '\n', 1, subread);
	status_error = 0;
	//if (*(read + subread) == '<' && *(read + subread + 1) != '\n')
	 	//Devien un cat normal - Ecrire cette partie
} */

char	*found_limiter(char *subread, int y, t_data *my_data)
{
	int		len;

	len = 0;
//	(void)read;
//	check_error_limiter(subread, read);
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

//! on peut utiliser l'historique dans le heredoc
/*char	*found_good_write(int len, char *read)
{
	if (read[len] == '|' && read[len + 1] != '|')
		return(ft_strdup("pipe heredoc> "));
	else if (read[len] == '|' && read[len + 1] == '|')
		return (ft_strdup("cmdor heredoc> "));
	else if (read[len] == '&' && read[len + 1] == '&')
		return (ft_strdup("cmdand heredoc> "));
	else
		return (ft_strdup("heredoc> "));
}*/

char	*found_name_fd_heredoc(void)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	int 	fd;

	i = 0;
	tmp1 = ft_itoa(i);
	tmp2 = ft_strjoin("/tmp/.here_doc", tmp1);
//	tmp2 = ft_strjoin(".here_doc", tmp1);
	fd = open(tmp2, O_CREAT, 777);
	printf("name is %s [%d]\n", tmp2, fd);
	while (++i && fd == -1)
	{
		free(tmp1);
		free(tmp2);
		tmp1 = ft_itoa(i);
		tmp2 = ft_strjoin("/tmp/.here_doc", tmp1);
//		tmp2 = ft_strjoin(".here_doc", tmp1);
		fd = open(tmp2, O_CREAT);
	}
	free(tmp1);
	close(fd);
	return (tmp2);
}

char	*write_heredoc(char *subread, int y, t_data *my_data)
{
	char	*lim;
	char	*line;
	char	*name_fd;
	int		fd;
//	int		len;

	while (subread[y] == ' ')
		y++;
	lim = found_limiter(subread, y, my_data);
	if (!lim)
		return (NULL);
	name_fd = found_name_fd_heredoc();
	printf("name of herdoc file is %s", name_fd); ///
	fd = open(name_fd, O_CREAT | O_WRONLY | O_TRUNC);
	printf(" and this fd is %d\n", fd); ///
	if (fd == -1)
		printf("bouh\n");
	write(1, ">", 1);
	line = get_next_line(STDIN_FILENO);
//	len = ft_strlen(lim);
	while (ft_strncmp(lim, line, ft_strlen(lim)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(lim);
	close(fd);
	return (name_fd);
}

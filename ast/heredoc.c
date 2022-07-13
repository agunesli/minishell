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

char	*found_limiter(char *subread, int y)
{
	int		len;

	len = 0;
//	(void)read;
//	check_error_limiter(subread, read);
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
	tmp2 = ft_strjoin("~/tmp/.here_doc", tmp1);
	printf("tmp1 is %s, tmp2 is %s\n", tmp1, tmp2);
	fd = open(tmp2, 1);
	while (++i && fd != -1)
	{
		free(tmp1);
		free(tmp2);
		tmp1 = ft_itoa(i);
		tmp2 = ft_strjoin("~/tmp/.here_doc", tmp1);
		printf("tmp1 is %s, tmp2 is %s\n", tmp1, tmp2);
	}
	free(tmp1);
	close(fd);
	return (tmp2);
}

char	*write_heredoc(char *subread, int y)
{
	char	*lim;
	char	*line;
	char	*name_fd;
	int		fd;
//	int		len;
	
	while (subread[y] == ' ')
		y++;
	lim = found_limiter(subread, y);
//	if (!lim)
		//Error limitateur
	name_fd = found_name_fd_heredoc();
	fd = open_file(name_fd, 2); // Reprendre cette fonction !!
//	if (fd == -1)
		//message d'erreur
	write(1, ">", 1);
//	if (write(1, ">", 1) == -1)
	//	merror("Error with write pipe heredoc\n"); //Modifier le message d'erreur
	line = get_next_line(STDIN_FILENO);
//	len = ft_strlen(lim);
	while (ft_strncmp(lim, line, ft_strlen(lim)))
	{
		write(fd, line, ft_strlen(line));
	//	if (write(fd, line, ft_strlen(line)) == -1)
	//		merror("Error with write in .here_doc\n"); //Modifier le message d'erreur
		free(line);
		write(1, ">", 1);
	//	if (write(1, ">", 1) == -1)
	//		merror("Error with write pipe heredoc\n"); //Modifier le message d'erreur
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(lim);
	close(fd);
	//if (close(fd) == -1)
//		merror("Error wtih close .here_doc\n");
	return (name_fd);
}
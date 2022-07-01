#include "minishell.h"
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

char	*found_limiter(char *subread, char *read)
{
	int		len;

	len = 0;
//	check_error_limiter(subread, read);
	while (subread[len] && (!ft_is_in_set(subread[len], MEDIUM)
				&& subread[len] != ' ')
		len++;
	return (ft_substr(subread, 0, len));
}

//! on peut utiliser l'historique dans le heredoc
char	*found_good_write(int len, char *read)
{
	if (read[len] == '|' && read[len + 1] != '|')
		return(ft_strdup("pipe heredoc> "));
	else if (read[len] == '|' && read[len + 1] == '|')
		return (ft_strdup("cmdor heredoc> "));
	else if (read[len] == '&' && read[len + 1] == '&')
		return (ft_strdup("cmdand heredoc> "));
	else
		return (ft_strdup("heredoc> "));
}

int	write_heredoc(char *subread, int y, char *read)
{
	char	*lim;
	char	*line;
	char	*msg;
	int		fd;
	int		len;
	
	while (subread[y] == ' ')
		y++;
	lim = found_limiter(subread, read);
//	if (!lim)
		//Error limitateur
	msg = found_good_write(ft_strlen(subread) + 1, read);
	fd = open_file("~/tmp/.here_doc", 2); // Reprendre cette fonction !!
//	if (fd == -1)
		//message d'erreur
	if (write(1, msg, ft_strlen(msg)) == -1)
	//	merror("Error with write pipe heredoc\n"); //Modifier le message d'erreur
	line = get_next_line(STDIN_FILENO);
	len = ft_strlen(lim);
	while (ft_strncmp(lim, line, len))
	{
		if (write(fd, line, ft_strlen(line)) == -1)
	//		merror("Error with write in .here_doc\n"); //Modifier le message d'erreur
		free(line);
		if (write(1, msg, ft_strlen(msg)) == -1)
	//		merror("Error with write pipe heredoc\n"); //Modifier le message d'erreur
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(lim);
	free(msg);
	if (close(fd) == -1)
//		merror("Error wtih close .here_doc\n");
	return (len);
}

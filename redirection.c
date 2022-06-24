#include "minishell.h"


// Pour <<< Error  zsh: parse error near %c, read[len] 
// Mais pour <<<erig juste un cat normal
// Mais pour <<<< Error zsh: parse error near `<' (peu importe ce qui suit)
// Attention pour le message d'erreur si LIM&& Error zsh: parse error near '&&' Idem pour '||' 
char	*found_limiter(char *read)
{
	int		len;
	int		i;
	char	*lim;

	len = 0;
	i = -1;
	if (read[len] == ' ' || read[len] == '|' || read[len] == '&'
			|| read[len] == '<' || read[len] == '>' || read[len] == '\n')
		return (NULL)	 // error zsh: parse error near %c, read[len] && pour '<' voir au haut !
	while (read[len] != ' ' || read[len] != '|' || read[len] != '&'
			|| read[len] != '<' || read[len] != '>' || read[len] != '\n')
		len++;
	lim = malloc(sizeof(char) * (len + 1));
	if (!lim)
		return (NULL); // utiliser plutot la fonction exit 
	while (++i < len)
		lim[i] = read[i];
	lim[i] = '\0';
	return (lim);
}

//! on peut utiliser l'historique dans le heredoc
char	*found_good_write(char *read)
{
	int		len;

	len = 0;
	while (read[len] != ' ' || read[len] != '|' || read[len] != '&'
			|| read[len] != '<' || read[len] != '>' || read[len] != '\n')
		len++;
	if (read[len] == '|' && read[len] != '|')
		return(ft_strdup("pipe heredoc> "));
	else if (read[len] == '|' && read[len] == '|')
		return (ft_strdup("cmdor heredoc> "));
	else if (read[len] == '&' && read[len] == '&')
		return (ft_strdup("cmdand heredoc> "));
	else
		return (ft_strdup("heredoc> "));
}

t_syntax	*heredoc(char *read)
{
	char	*lim;
	char	*line;
	int		fd;

	lim = found_limiter(read);
	fd = open("~/tmp/.here_doc", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (fd == -1)
		merror("Error with open .here_doc\n"); // Mettre un message d'erreur par defaut
	if (write(1, "pipe heredoc>", 13) == -1)
		merror("Error with write pipe heredoc\n");
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(lim, line, ft_strlen(lim)))
	{
		if (write(fd, line, ft_strlen(line)) == -1)
		s = 
	s = "heredoc>\n";
}

void	write_heredoc(char *read)
{
	char	*lim;
	char	*line;
	char	*msg;
	int		fd;

	lim = found_limiter(read);
	msg = found_good_write(read);
	fd = open_file("~/tmp/.here_doc", 1);
	/*fd = open("~/tmp/.here_doc", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (fd == -1)
		merror("Error with open .here_doc\n"); // Mettre un message d'erreur par defaut*/
	if (write(1, msg, ft_strlen(msg)) == -1)
		merror("Error with write pipe heredoc\n"); //Modifier le message d'erreur
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(lim, line, ft_strlen(lim)))
	{
		if (write(fd, line, ft_strlen(line)) == -1)
			merror("Error with write in .here_doc\n"); //Modifier le message d'erreur
		free(line);
		if (write(1, msg, ft_strlen(msg)) == -1)
			merror("Error with write pipe heredoc\n"); //Modifier le message d'erreur
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(lim);
	free(msg);
	if (close(fd) == -1)
		merror("Error wtih close .here_doc\n");
	//return (fd);
}

t_syntax	*heredoc(char *read)
{
	int			fd;
	t_syntax	*syn;

	write_heredoc(read);
	syn->id = heredoc;
	syn->content = ft_strdup("~/tmp/.here_doc");
	syn->left = NULL;
	syn->right = NULL;
	return (syn)
}

t_syntax	*change_stdin(char *read)
{
	syn->id = in;
	syn->content = ft_strdup("~/tmp/.here_doc"); // A MODIFIER
	syn->left = NULL;
	syn->right = NULL;
	return (syn);
}

t_syntax	*rediction_in(char *read, int y)
{
	if (y == -1)
		low_piece(read); // fonction a faire
	else if (read[y] == '<' && read[y + 1] == '<')
		return(heredoc(read + y + 2));
		//syn.id = heredoc;
	else if (read[y] == '<' && read[y + 1] != '<')
		return (change_stdin(read + y + 1));
}


// FONCTION A RETRAVAILLER !!
t_syntax	*rediction_out(char *read, int y)
{
	else if (read[y] == '>' && read[y + 1] == '>')
		return(heredoc(read + y + 2));
	else if (read[y] == '>' && read[y + 1] != '>')
		return (change_stdin(read + y + 1));
}

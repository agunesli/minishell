#include "minishell.h"

t_syntax	*heredoc(char *subread, char *read)
{
	int			fd;
	t_syntax	*syn;

	write_heredoc(subread, read);
	syn->id = heredoc;
	syn->content = ft_strdup("~/tmp/.here_doc");
	syn->left = NULL;
	syn->right = NULL;
	return (syn)
}
/*
char	*found_name_fd(char *read)
{
	

	while (*read == ' ')
		read++;
	if (read[len] == '\n' || read[len] == '|' || read[len] == '&'
			|| read[len] == '<' || read[len] == '>')
		return (NULL)	 // error zsh: parse error near %c, read[len] && pour '<' voir au haut !
}

t_syntax	*change_stdin(char *read)
{
	syn->id = in;
	syn->content = ft_strdup("~/tmp/.here_doc"); // A MODIFIER (fonction pour trouver le nom du fichier)
	syn->left = NULL;
	syn->right = NULL;
	return (syn);
}
*/
t_syntax	*redirection_in(char *subread, int y, char *read)
{
	if (subread[y] == '<' && subread[y + 1] == '<')
		return(heredoc(read + y + 2, read));
	else if (read[y] == '<' && read[y + 1] != '<')
		return (change_stdin(read + y + 1, read));
}

// FONCTION A RETRAVAILLER !!
t_syntax	*redirection_out(char *read, int y)
{
	else if (read[y] == '>' && read[y + 1] == '>')
		return(heredoc(read + y + 2));
	else if (read[y] == '>' && read[y + 1] != '>')
		return (change_stdin(read + y + 1));
}

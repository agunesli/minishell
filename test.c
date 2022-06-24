#include "minishell.h"

t_syntax	*medium_piece(char *subread, char *read)
{
	t_syntax	*syn;
	int			i;

	i = 0;
	while (subread[i] && !ft_is_in_set(subread[i], MEDIUM))
		i++;
	if (i == ft_strlen(subread))
		syn = low_piece(ft_strdup(subread));	
	else if (subread[i] == '<')
		return (redirection_in(subread, i, read));
	else 
		return (redirection_out(subread, i, read)); 
}

int	strong_piece(char *read)
{
	t_syntax	*syn;
	int			i;

	i = 0;
	while (read[i] && !ft_is_in_set(read[i], STRONG))
		i++;
	if (i == ft_strlen(read))
		syn = medium_piece(ft_strdup(read));
	else
	{
		sym->content = NULL;
		if (read[i] == '|' && read[i + 1] != '|')
			sym->id = pipe;
		else if (read[i] == '|' && read[i + 1] == '|')
			sym->id = or;
		else if (read[i] == '&' && read[i + 1] == '&')
			sym->id = and;
/*		else // cas ou un seul & mais je ne connais pas le comportement !
			sym->*/
		syn->left = medium_piece(ft_substr(read, 0, i), read);
	}
	return (i);
}


// REFAIRE CETTE FONCTION
t_syntax	parser(char *read)
{
	t_syntax *syn;
	int	x;

	x = found_strong_piece(read);
	if (x == -1)
		syn = medium_piece(read, x); // fonction a faire
	sym->content = NULL;
	if (read[x] == '&')
		syn->id = AND;
	else if (read[x] == '|' && read[x + 1] == '|')
		syn->id = OR;
	else
		syn->id = pipe;
	syn->left = found_medium_piece(ft_substr(read, 0, x));
	//reflechir pour bien positionner pour la recursion
}

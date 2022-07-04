#include "minishell.h"

// cmd
// star
// single quote
// double quote
// $
// $?
t_syntax	*low_piece(char *subread, char *read) //cmd
{
 	t_syntax	*syn;
 	int			i;
 	char		**word

 	if (!subread)
 		return (NULL);
	i = good_place(subread, LOW, 0);
	if (i == (int)ft_strlen(subread))
 /*	if (i == ft_strlen(subread))
 		not_dollar(subread, read); // fonction a faire
 	while (subread[i] && !ft_is_in_set(subread[i], LOW) && !quote_before(subread, i))
 		i++;
 	if (i == ft_strlen(subread))
 	{
 		syn->id = cmd;
 		syn->content = ft_strdup(subread);
 	}
 	if (subread[i] == '$')
 	{
 		if (subread[i + 1] == '?')
 		{
 			syn->id = error;
 			syn->content = NULL;
 			syn->left =
 		}
 		else
 		{
 			syn->id = expand;
 			syn->content = found_word(subread, i);
 		}
 	}
 	else
 	{
 		syn->id = star;
 		syn->content = found_word_star(subread, i);
 	}*/
}


t_syntax	*medium_piece(char *subread, char *read)
{
	t_syntax	*syn;
	int			i;

	if (!subread)
		return (NULL);
	i = good_place(subread, MEDIUM, 0);
	if (i == (int)ft_strlen(subread))
		syn = low_piece(ft_strdup(subread), read);
	else
	{
/*		syn = malloc(sizeof(t_syntax));
		if (!syn)
			return (NULL);*/
		if (subread[i] == '<')
			syn = redirection_in(subread, i, read);
		else
			syn = redirection_out(subread, i, read);
	}
	free(subread);
	return (syn);
}

// arg malloc pour eviter pb avec free lors du premier lancement
t_syntax	*strong_piece(char *read) 
{
	t_syntax	*syn;
	int			i;
	char		*str;

	i = good_place(read, STRONG, 0);
	if (i == (int)ft_strlen(read))
		syn = medium_piece(ft_strdup(read), read);
	else
	{
		syn = malloc(sizeof(t_syntax));
		if (!syn)
			return (NULL);
		syn->content = NULL;
		if (read[i] == '|' && read[i + 1] != '|')
			syn->id = PIPE;
		else if (read[i] == '|' && read[i + 1] == '|')
			syn->id = OR;
		else if (read[i] == '&' && read[i + 1] == '&')
			syn->id = AND;
/*		else // cas ou un seul & mais je ne connais pas le comportement !
			sym->*/
		syn->left = medium_piece(ft_substr(read, 0, skip_space(read, i)), read);
		if (syn->id == PIPE)
			str = ft_substr(read, skip_space(read, i + 1), ft_strlen(read));
		else
			str = ft_substr(read, skip_space(read, i + 2), ft_strlen(read));
		syn->right = strong_piece(str);
	}
	free(read);
	return (syn);
}

// REFAIRE CETTE FONCTION
void	parser(char *read)
{
	t_syntax *syn;

	while (*read == ' ')
		read++;
	syn = strong_piece(ft_strdup(read));
	
/*	t_syntax *syn;
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
	syn->left = found_medium_piece(ft_substr(read, 0, x));*/
	//reflechir pour bien positionner pour la recursion
}

#include "minishell.h"

char	*after_space(char *subread)
{
	int	i;

	i = 0;
	while (subread[i] != ' ')
		i++;
	return (ft_substr(subread, i + 1, ft_strlen(subread));
}

// 34 double quote, 29 single quote 
/*int	quote_before(char *read, int x)
{
	int	i;
	int	cpt;

	i = ((cpt = 0, -1));
	while (++i < x)
	{
		if (read[i] == 34)
			cpt++;
	}
	if (cpt % 2 == 1)
		return (1);
	i = ((cpt = 0, -1));
	while (i < x)
	{
		if (read[i] == 39)
			cpt++;
	}
	if (cpt % 2 == 1)
		return (1);
	return (0);
}*/

char	*found_word(char *subread, int i)
{
	int	tmp;
	int	j;
	char	*str;

	tmp = i;
	j = 0;
	while (i > -1 && subread[i] != ' ')
		i--;
	while (subread[tmp] && subread[tmp] != ' ')
		tmp++;
	str = malloc(sizeof(char) * (tmp - i +1));
	if (!str)
		return (NULL);
	while (i < tmp)
	{
		str[j] = subread[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

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

	i = 0;	
	if (!subread)
		return (NULL);
	while (subread[i] == ' ')
		i++;
	while (subread[i] && !ft_is_in_set(subread[i], LOW) /*&& !quote_before(subread, i)*/)
		i++;
	if (subread[i] == '$')
	{
		if (subread[i + 1] == '?')
		{
			syn->id = error;
			syn->content = NUUL;
		}
		else
		{
			syn->id = expend;
			syn->content = found_word(subread, i);
		}
	}
	else 
	{
		syn->id = star;
			syn->content = found_word(subread, i);

	}

}

t_syntax	*medium_piece(char *subread, char *read)
{
	t_syntax	*syn;
	int			i;

	i = 0;
	if (!subread)
		return (NULL);
	while (subread[i] == ' ')
		i++;
	while (subread[i] && !ft_is_in_set(subread[i], MEDIUM) /*&& !quote_before(subread, i)*/)
		i++;
	if (i == ft_strlen(subread))
		syn = low_piece(ft_strdup(subread), read);	
	else
	{
		if (subread[i] == '<')
		{
			syn = redirection_in(subread, i, read);
			syn->right = low_piece(after_space(subread), read);
		}
		else
		{
			syn = redirection_out(subread, i, read);
			syn->right = low_piece(ft_substr(subread, 0, i), read);
		}
	}
	free(subread);
	return (syn);
}

t_syntax	*strong_piece(char *read) // arg malloc pour eviter pb avec free lors du premier lancement 
{
	t_syntax	*syn;
	int			i;
	char		*str;

	i = 0;
	while (read[i] && !ft_is_in_set(read[i], STRONG)/* && !quote_before(read, i)*/)
		i++;
	if (i == ft_strlen(read))
		syn = medium_piece(ft_strdup(read), read);
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
		if (sym->id == pipe)
			str = ft_substr(read, i + 1, ft_strlen(read));
		else
			str = ft_substr(read, i + 2, ft_strlen(read));
		syn->right = strong_piece(str);
	}
	free(read); 
	return (syn);
}


// REFAIRE CETTE FONCTION
t_syntax	parser(char *read)
{
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

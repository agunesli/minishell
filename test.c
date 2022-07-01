#include "minishell.h"

char	*found_word(char *subread, int i)
{
	int	len;
	int	j;

	j = i - 1;
	while (subread[++j] != ' ')
		len++;
	return (ft_substr(subread, i, len));
}

char	*found_word_star(char *subread, int i)
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
	str = malloc(sizeof(char) * (tmp - i + 1));
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

int	skip_space(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

// 34 double quote, 29 single quote
int	good_place(char *read, char *set, int i)
{
	char	c;

	while (read[i] && !ft_is_in_set(read[i], set)
			&& read[i] != 34 && read[i] != 39)
		i++;
	c = read[i];
	if (c == 34 || c == 39)
	{
		i++;
		while(read[i] && read[i] != c)
			i++;
		if (!read[i])
			//error syntax quote no close
		return (good_place(read, set, i);
	}
	else 
		return (i);
}

// cmd
// star
// single quote
// double quote
// $
// $?
// t_syntax	*low_piece(char *subread, char *read) //cmd
// {
// 	t_syntax	*syn;
// 	int			i;
// 	char		**word;

// 	i = 0;
// 	if (!subread)
// 		return (NULL);
// /*	while (*subread == ' ')
// 		subread++;
// 	while (subread[i] == '$')
// 		i++;
// 	if (i == ft_strlen(subread))
// 		not_dollar(subread, read); // fonction a faire */
// 	while (subread[i] && !ft_is_in_set(subread[i], LOW) /*&& !quote_before(subread, i)*/)
// 		i++;
// 	if (i == ft_strlen(subread))
// 	{
// 		syn->id = cmd;
// 		syn->content = ft_strdup(subread);
// 	}
// 	if (subread[i] == '$')
// 	{
// 		if (subread[i + 1] == '?')
// 		{
// 			syn->id = error;
// 			syn->content = NULL;
// 			syn->left =
// 		}
// 		else
// 		{
// 			syn->id = expand;
// 			syn->content = found_word(subread, i);
// 		}
// 	}
// 	else
// 	{
// 		syn->id = star;
// 		syn->content = found_word_star(subread, i);
// 	}
// }


t_syntax	*medium_piece(char *subread, char *read)
{
	t_syntax	*syn;
	int			i;

	if (!subread)
		return (NULL);
	i = good_place(subread, LOW, 0);
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

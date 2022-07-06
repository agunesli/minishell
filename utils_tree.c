#include "minishell.h"

int	ft_is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*found_word(char *subread, int i)
{
	int	len;
	int	j;

	j = i - 1;
	len = 0;
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
//		if (!read[i])
			//error syntax quote no close
		return (good_place(read, set, i));
	}
	else
		return (i);
}

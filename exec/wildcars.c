#include "../minishell.h"

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

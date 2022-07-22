#include "../minishell.h"

int	found_char(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int	id_check(char *str, int i)
{
	int	len;
	int	j;

	j = -1;
	if (i == -1)
		len = ft_strlen(str);
	else
		len = i;
	if (str[0] && ft_isdigit(str[0]))
			return (0);
	while (str[++j] && j < len)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
	}
	return (1);
}

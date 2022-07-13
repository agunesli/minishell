#include "../minishell.h"

char	**separate_word(char *cmd, char **dest)
{
	int		i;
	int		len;
	int		j;

	i = 0;
	j = -1;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		len = good_place(cmd, " ", i) - i;
//		printf("i is %d and len is %d\n", i, len); //
		dest[++j] = ft_substr(cmd, i, len);
//		printf("dest[j] = %s\n", dest[j]); //
		i+=(len);
	}
	printf("j is %d\n", j + 1);
	dest[++j] = NULL;
	return (dest);
}

int	cpt_good_space(char *cmd)
{
	int		cpt;
	char	c;
	int		i;

	i = -1;
	cpt = 0;
	while (cmd[++i])
	{
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != 34 && cmd[i] != 39)
			i++;
		c = cmd[i];
		if (c == 34 || c == 39)
		{
			i++;
			while(cmd[i] && cmd[i] != c)
				i++;
		}
		else
		{
			cpt++;
			while(cmd[i] && cmd[i] == c)
				i++;
		}
	}
	return (cpt);
}

char	**separate(char *cmd)
{
	int		cpt;
	char	**dest;

//	printf("cmd start separate %s\n", cmd);
	cpt = cpt_good_space(cmd);
	printf("cpt is %d\n", cpt);
	dest = malloc(sizeof(char *) * (cpt + 1));
	if (!dest)
		return (NULL);
	return (separate_word(cmd, dest));
}

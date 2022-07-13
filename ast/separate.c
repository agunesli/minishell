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
//	printf("j is %d\n", j + 1);
	dest[++j] = NULL;
	free(cmd);
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
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\'' && cmd[i] != '\"')
			i++;
		c = cmd[i];
//		printf("c is %c i is %d\n", c, i);
		if (c == '\'' || c == '\"')
		{
			i++;
			while(cmd[i] && cmd[i] != c)
				i++;
//			printf("i after quote %d\n", i);
		}
		else if (c == ' ')
		{
//			printf("prout\n");
			cpt++;
			//i++;
			while(cmd[i] && cmd[i] == c && cmd[i + 1] != '\'' 
					&& cmd[i + 1] != '\"')
				i++;
			/*if (cmd[i] == '\'' || cmd[i] == '\"')
				i--;*/
//			printf("i after cpt %d => %c\n", i, cmd[i]);
		}
	}
	return (cpt);
}

char	**separate(char *cmd)
{
	int		cpt;
	char	**dest;

//	printf("cmd start separate %s [%ld]\n", cmd, ft_strlen(cmd));
	cpt = cpt_good_space(cmd);
//	printf("cpt is %d\n", cpt);
	dest = malloc(sizeof(char *) * (cpt + 2));
	if (!dest)
		return (NULL);
	return (separate_word(cmd, dest));
}

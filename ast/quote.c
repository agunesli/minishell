#include "../minishell.h"

int	len_arg(char *cmd)
{
	int		i;
	int		cpt;
	char	c;

	i = -1;
	cpt = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			while (cmd[++i] && cmd[i] != c)
				;
			if (cmd[i])
				cpt+=2;
			else
				return (-1);
		}
	}
	return (cpt);
}

char	*without_quote(char *cmd)
{
	int		cpt;
	char	*dest;
	int		i;
	int		j;
	char	c;

	cpt = len_arg(cmd);
//	printf("cpt is %d\n", cpt);
	i = ((j = -1, -1));
//	if (cpt == -1)
//		error ?
	if (cpt == 0)
		return (cmd);
	if (cpt == (int)ft_strlen(cmd))
	{
		free(cmd);
		return (ft_strdup(" ")); //Demander a Gurvan si c'est bon pour lui
	}
	dest = malloc(sizeof(char) * (ft_strlen(cmd) - cpt + 1));
	if (!dest)
		return (NULL);
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			while(cmd[++i] && cmd[i] != c)
				dest[++j] = cmd[i];
		}
		else
				dest[++j] = cmd[i];
	}
	dest[++j] = '\0';
	free(cmd);
	return (dest);
}

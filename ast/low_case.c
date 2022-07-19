#include "../minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	tmp2 = ft_strjoin(tmp1, s3);
	free(s3);
	free(tmp1);
	return (tmp2);
}

// = $ ~ * "'
char	**change_cmd(char *cmd, t_data *my_data)
{
	int		i;
	char	**dest;

	i = -1;
//	(void)my_data;
	cmd = expand(cmd, my_data);
	dest = separate(cmd);
	while (dest[++i] != NULL)
	{
		dest[i] = without_quote(dest[i]);
	}
	return (dest);
}

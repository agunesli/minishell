#include "../minishell.h"

char	*found_word_expand(char *subread, int i)
{
	int	len;
	int	j;

	j = i - 1;
	len = 0;
	if (subread[i] == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(subread[i]))
		return (ft_itoa(subread[i] - 48));
	while (subread[++j] && (ft_isalnum(subread[j]) || subread[j] == '_'))
		len++;
	return (ft_substr(subread, i, len));
}

char	*found_expand(char *expand, t_data *my_data)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!expand)
		return (NULL);
	if (!ft_strncmp(expand, "?", 2))
		return (ft_itoa(g_error));
	else if (ft_isdigit(expand[i + 1]))
		return (ft_strdup(""));
	while (my_data->env[++i] != NULL)
	{
		tmp = ft_strjoin(expand, "=");
		if (!ft_strncmp(tmp, my_data->env[i], ft_strlen(tmp)))
			return (ft_strdup((my_data->env[i] + ft_strlen(expand) + 1)));
		free(tmp);
	}
	return (NULL); //Cas d'erreur !!
}

char	*change_expand(char *cmd, int i, t_data *my_data)
{
	char	*part1;
	char	*part2;
	char	*expand;
	char	*result;
	int		start2;

	part1 = ft_substr(cmd, 0, i);
	expand = found_word_expand(cmd, i + 1);
	result = found_expand(expand, my_data);
	start2 = i + ft_strlen(expand) + 1;
	part2 = ft_substr(cmd, start2, ft_strlen(cmd) - start2);
	free(cmd);
	free(expand);
	if (!result || !result[0])
		return (ft_strjoin(part1, part2));
	else
		return (ft_strjoin3(part1, result, part2));
}

char	*expand(char *cmd, t_data *my_data)
{
	int		i;
	int		quote;
	int		dbl;

	if (!cmd)
		return (NULL);
	i = -1;
	quote = 1;
	dbl = 0;
	while (cmd[++i])
	{
		if (quote % 2 && cmd[i] == '\"')
			dbl++;
		else if (!(dbl % 2) && cmd[i] == '\'')
			quote++;
		else if (cmd[i] == '$' && dbl % 2
				&& /*(cmd[i + 1] == '\'' || cmd[i + 1] == '\"' 
					|| */(cmd[i + 1] == '$' || !cmd[i + 1])) 
				i++;
		else if (cmd[i] == '$' && quote % 2)
			return (expand(change_expand(cmd, i, my_data), my_data));
	}
	return (cmd);
}

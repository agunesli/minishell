#include "../minishell.h"

char	*found_word_expand(char *subread, int i)
{
	int	len;
	int	j;

	j = i - 1;
	len = 0;
	while (subread[++j] && subread[j] != ' ' && subread[j] != '\"')
		len++;
	return (ft_substr(subread, i, len));
}

char	*expand_error(char *expand, t_data *my_data)
{
	char	*dst;
	char	*tmp1;
	char	*tmp2;

	if (expand[1] == ' ' || expand[1] == '\n')
		return (ft_itoa(my_data->status_error));
	tmp1 = ft_itoa(my_data->status_error);
	tmp2 = ft_substr(expand, 1, ft_strlen(expand));
	dst = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (dst);
}

char	*found_expand(char *expand, t_data *my_data)
{
	int	i;

	i = -1;
	if (!ft_strncmp(expand, "?", 1))
		return (expand_error(expand, my_data));
	while (my_data->env[++i] != NULL)
	{
		if (!ft_strncmp(expand, my_data->env[i], ft_strlen(expand)))
			return (ft_strdup((my_data->env[i] + ft_strlen(expand) + 1)));
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
	start2 = i + ft_strlen(expand) + 1;
	part2 = ft_substr(cmd, start2, ft_strlen(cmd) - start2);
	result = found_expand(expand, my_data);
	free(cmd);
	free(expand);
	return (ft_strjoin3(part1, result, part2));
}

// A FAIRE QUE ENTRE ""
char	*expand(char *cmd, t_data *my_data)
{
	int		i;
	int		quote;

	i = -1;
	quote = 1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'')
			quote++;
		else if (cmd[i] == '$' && quote%2)
			return (expand(change_expand(cmd, i, my_data),my_data));
	}
	return (cmd);
}

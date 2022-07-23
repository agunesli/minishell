#include "../minishell.h"

int	found_id(char *cmd,  char **env, t_data *my_data)
{
	int	i;
	char	*id;
	char	*pos;

	i = -1;
	id = ft_strjoin(cmd, "=");
	if (!ft_strncmp(id, "PATH=", 5))
		my_data->path = NULL;
	pos = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(id, env[i], ft_strlen(id)))
		{
			pos = (env[i]);
			break ;
		}
	}
	if (!ft_strncmp(id, "SHLVL=", 6))
	{
		env[i] = ft_strdup("SHLVL=0");
		pos = NULL;
	}
	free(id);
	if (pos)
		return (i);
	return (-1);
}

char	**update_env(char *cmd, char **env, t_data *my_data)
{
	int 	pos;
	int		len;
	int		i;
	char	*tmp;

	pos = found_id(cmd, env, my_data);
	len = len_split(env);
	i = -1;
	if (pos == -1)
		return (env);
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return (NULL);
	while (++i < pos)
		tmp[i] = env[i];
	while (env[++i])
		tmp[i - 1] = env[i];
	tmp[i] = NULL;
	free(env[i]);
	free(env);
	return (tmp);
}

int	ft_unset(char **cmd, t_data *my_data)
{
	int	i;

	i = 0;
	if (cmd[1] == NULL)
		return (0);
	while (cmd[++i])
	{
		if (!id_check(cmd[i], -1))
			printf("bash : export: '%s' : not a valid identifier\n", cmd[i]); //Error 1
		else
			my_data->env = update_env(cmd[i], my_data->env, my_data);
	}
	return (0);
}

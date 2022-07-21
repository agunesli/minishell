#include "../minishell.h"

int	id_is_in_env(char **env, char *cmd, int len)
{
	int	i;
	char	*id;
	char	*pos;

	i = -1;
	id = ft_substr(cmd, 0, len + 1);
	// printf("id is %s\n", id);
	pos = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(id, env[i], ft_strlen(id)))
		{
			pos = (env[i]);
			break ;
		}
	}
	if (pos)
	{
		free(env[i]);
		env[i] = ft_strdup(cmd);
		return (1);
	}
	free(id);
	return (0);
}

int	id_is_in_exprt(char **exprt, char *cmd)
{
	int	i;
	char	*pos;

	i = -1;
	// printf("id is %s\n", id);
	pos = NULL;
	while (exprt[++i])
	{
		if (!ft_strncmp(cmd, exprt[i], ft_strlen(cmd)))
		{
			pos = (exprt[i]);
			break ;
		}
	}
	if (pos)
	{
	//	free(exprt[i]);
		while (exprt[++i])
			exprt = exprt[i + 1];
		cmd[i] = pos;
		return (1);
	}
	return (0);
}
void	change_env(t_data *my_data, char **dst, int len)
{
	if (!id_is_in_env(my_data->env, dst[0], len))
		my_data->env = ft_strjointab(my_data->env, dst);
}

void	change_exprt(t_data *my_data, char **dst)
{
	if (!id_is_in_exprt(my_data->exprt, dst[0]))
		my_data->exprt = ft_strjointab(my_data->exprt, dst);
}

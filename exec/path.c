#include "../minishell.h"

char	**found_path_env(char **env, t_data *my_data)
{
	int		i;
	char	*path;
	char	*tmp;
	char	**bin;

	i = -1;
	path = NULL;
	while (env[++i] != NULL)
	{
		if (!ft_strncmp("PATH=/", env[i], 6))
		{
			path = ft_strdup(env[i]);
			break ;
		}
	}
	if (path == NULL && !my_data->path)
		errorp(my_data->all_cmd[my_data->crt][0]);
	// bash : cat: No such file or directory
	else if (my_data->path)
		path = ft_strdup(my_data->path);
//	ATTENTION LES COMMANDES NE FONCTIONNENT PLUS SSI UNSET PATH 
//	(fonctionnent si on fait unset path)
	tmp = path;
	path = ft_substr(tmp, 5, ft_strlen(tmp) - 5);
	free(tmp);
	bin = ft_split(path, ':');
	free(path);
	return (bin);
}

int	len_bin(char **bin)
{
	int	i;

	i = 0;
	while (bin[i])
		i++;
	return (i);
}

int	is_dir(char *cmd)
{
	if(open(cmd, __O_DIRECTORY) != -1)
	{
		putstr_error("bash: ");
		putstr_error(cmd);
		putstr_error(": ");
		putstr_error(strerror(21));
		putstr_error("\n");
		return (1);
	}
	return (0);
}

char	*correct_path(char **cmd, t_data *my_data)
{
	char	**bin;
	char	*tmp;
	int		i;
	int		len;
	char	*cmdd;

	i = 0;
	if (access(cmd[0], F_OK) == 0 && is_dir(cmd[0]))
	{
//		if(is_dir(cmd[0]))
		return (NULL);
	}
	if (access(cmd[0], F_OK | X_OK) == 0 || ft_strrchr(cmd[0], '/'))
		return (cmd[0]);
	bin = found_path_env(my_data->env, my_data);
	len = len_bin(bin);
	cmdd = ft_strjoin("/", cmd[0]);
	tmp = ft_strjoin(bin[0], cmdd);
//	if(!ft_strrchr(cmd[0], '/'))
//	{
	while (++i < len && access(tmp, F_OK | X_OK))
	{
//		printf("path is %s\n", tmp);
		free(tmp);
		tmp = ft_strjoin(bin[i], cmdd);
	}
//	}
	free(cmdd);
	free_all(bin);
	if (i == len)
		return (error_command(cmd[0], my_data), NULL);
	else
		return (tmp);
}

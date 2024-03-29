/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:43:51 by tamather          #+#    #+#             */
/*   Updated: 2022/09/07 01:31:28 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (errorp(my_data->all_cmd[my_data->crt][0], my_data), NULL);
	else if (my_data->path)
		path = ft_strdup(my_data->path);
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
	while (bin && bin[i])
		i++;
	return (i);
}

int	is_dir(char *cmd, t_data *my_data)
{
	if (open(cmd, __O_DIRECTORY) != -1)
	{
		putstr_error("bash: ");
		putstr_error(cmd);
		putstr_error(": ");
		putstr_error(strerror(21));
		putstr_error("\n");
		g_error = 126;
		free_all(my_data->env);
		ft_free_necessary(my_data);
		exit(g_error);
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

	i = -1;
	if (access(cmd[0], F_OK) == 0 && is_dir(cmd[0], my_data))
		return (NULL);
	if (access(cmd[0], F_OK | X_OK) == 0 || ft_strrchr(cmd[0], '/'))
		return (cmd[0]);
	bin = found_path_env(my_data->env, my_data);
	if (!bin)
		return (NULL);
	len = len_bin(bin);
	cmdd = ft_strjoin("/", cmd[0]);
	tmp = ft_strjoin(bin[0], cmdd);
	while (++i < len && access(tmp, F_OK | X_OK))
		tmp = ((free(tmp), ft_strjoin(bin[i], cmdd)));
	free(cmdd);
	free_all(bin);
	if (i == len)
		return (free(tmp), error_command(cmd[0], my_data), NULL);
	else
		return (tmp);
}

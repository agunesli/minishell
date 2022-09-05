#include "../minishell.h"

int	print_only_export(char **env, char **exprt)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		write(1, "export ", 7);
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
	if (exprt)
		print_only_export(exprt, NULL);
	return (0);
}

int	do_export(char **cmd, t_data *my_data)
{
	int		i;
	int		pos_eg;
	char	**dst;

	i = 0;
	while (cmd[++i])
	{
		pos_eg = found_char(cmd[i], '=');
		if (!cmd[i][0] || !pos_eg || !id_check(cmd[i], pos_eg))
			return (error_invalid_id(cmd[i]));
		else
		{
			if (!ft_strncmp("PATH=", cmd[i], 5))
			{
				free(my_data->path);
				my_data->path = NULL;
			}
			dst = change_str_to_tab(cmd[i]);
			if (pos_eg == -1)
				change_exprt(my_data, dst);
			else if (pos_eg > 0)
				change_env(my_data, dst, pos_eg);
		}
	}
	return (0);
}

int	ft_export(char **cmd, t_data *my_data)
{
	if (cmd[1] == NULL)
		return (print_only_export(my_data->env, my_data->exprt));
	else
		return (do_export(cmd, my_data));
}

#include "../minishell.h"

void	print_only_export(char **env, char **exprt)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		write(1, "export ", 7);
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
	if (!exprt)
		return ;
	else
		print_only_export(exprt, NULL);
}

void	do_export(char **cmd, t_data *my_data)
{
	int	i;
	int pos_eg;
	char	**dst;

	i = 0;
	while (cmd[++i])
	{
		pos_eg = found_char(cmd[i], '=');
		if (!pos_eg || !id_check(cmd[i], pos_eg))
			printf("bash : export: '%s' : not a valid identifier\n", cmd[i]); //Error 1
		else
		{
			dst = change_str_to_tab(cmd[i]);
			if (pos_eg == -1)
				change_exprt(my_data, dst);
			else if (pos_eg > 0)
				change_env(my_data, dst, pos_eg);
		}
	}
}

int	ft_export(char **cmd, t_data *my_data)
{
	if (cmd[1] == NULL)
		print_only_export(my_data->env, my_data->exprt);
	else
		do_export(cmd, my_data);
	return (0);
}

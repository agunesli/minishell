#include "../minishell.h"

void	print_only_export(char **env, char **exprt)
{
	int	i;

	i = -1;
//	print_all(env);
	while (env[++i])
	{
		write(1, "export ", 7);
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
//	printf("\n\n\n\n\n");
	// sleep(2);
	if (!exprt)
		return ;
	else
		print_only_export(exprt, NULL);
}

int	found_char(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int	id_check(char *str, int i)
{
	int	len;
	int	j;

	j = -1;
	if (i == -1)
		len = ft_strlen(str);
	else
		len = i;
	if (str[0] && ft_isdigit(str[0]))
			return (0);
	while (str[++j] && j < len)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
	}
	return (1);
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
			printf("bash : export: '%s' : not a valid identifier\n", cmd[i]);
		else
		{
			dst = change_str_to_tab(cmd[i]);
			if (pos_eg == -1)
				change_export(my_data, dst);
				// my_data->exprt = ft_strjointab(my_data->exprt, dst);
			else if (pos_eg > 0)
				change_env(my_data, dst, pos_eg);
		}
	}
}

int	ft_export(char **cmd, t_data *my_data)
{
//	(void)cmd;
//	(void)my_data;
//	printf("bouf\n");
	if (*(cmd + 1) == NULL)
		print_only_export(my_data->env, my_data->exprt);
	else
		do_export(cmd, my_data);
	return (0);
}

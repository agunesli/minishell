#include "../minishell.h"


int	is_builtins(t_data *my_data)
{
	int	crt;

	crt = my_data->crt;
	if (!my_data->all_cmd[0])
		return (0);
	if (!ft_strncmp("echo", my_data->all_cmd[crt][0], ft_strlen("echo") + 1))
		return (b_echo);
	if (!ft_strncmp("pwd", my_data->all_cmd[crt][0], ft_strlen("pwd") + 1))
		return (b_pwd);
	if (!ft_strncmp("cd", my_data->all_cmd[crt][0], ft_strlen("cd") + 1))
		return (b_cd);
	if (!ft_strncmp("exit", my_data->all_cmd[crt][0], ft_strlen("exit") + 1))
		return (b_exit);
	if (!ft_strncmp("export", my_data->all_cmd[crt][0], ft_strlen("export") + 1))
		return (b_exprt);
	if (!ft_strncmp("unset", my_data->all_cmd[crt][0], ft_strlen("unset") + 1))
		return (b_unset);
	if (!ft_strncmp("env", my_data->all_cmd[crt][0], ft_strlen("env") + 1))
		return (b_env);
	return (0);
}

int	hub_builtins(int opt, t_data *my_data)
{
	if (opt == b_echo)
		return (ft_echo(my_data->all_cmd[my_data->crt], my_data));
	if (opt == b_pwd)
		return (ft_pwd(my_data->all_cmd[my_data->crt], my_data));
	if (opt == b_cd)
		return (ft_cd(my_data->all_cmd[my_data->crt], my_data));
	if (opt == b_exit)
		return (ft_exit(my_data->all_cmd[my_data->crt], my_data));
	if (opt == b_exprt)
		return (ft_export(my_data->all_cmd[my_data->crt], my_data));
	if (opt == b_unset)
		return (ft_unset(my_data->all_cmd[my_data->crt], my_data));
	if (opt == b_env)
		return (ft_env(my_data->all_cmd[my_data->crt], my_data));
	return (-1);
}


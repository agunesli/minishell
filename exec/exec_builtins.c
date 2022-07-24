#include "../minishell.h"

int	is_builtins(t_data *my_data)
{
	if (my_data->nb_process == 1)
		good_fd(my_data->syn, my_data);
	if (!ft_strncmp("echo", my_data->all_cmd[0][0], ft_strlen("echo") + 1))
		return (ft_echo(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("pwd", my_data->all_cmd[0][0], ft_strlen("pwd") + 1))
		return (ft_pwd(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("cd", my_data->all_cmd[0][0], ft_strlen("cd") + 1))
		return (ft_cd(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("exit", my_data->all_cmd[0][0], ft_strlen("exit") + 1))
		return (ft_exit(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("export", my_data->all_cmd[0][0], ft_strlen("export") + 1))
		return (ft_export(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("unset", my_data->all_cmd[0][0], ft_strlen("unset") + 1))
		return (ft_unset(my_data->all_cmd[my_data->crt], my_data));
	if (!ft_strncmp("env", my_data->all_cmd[0][0], ft_strlen("env") + 1))
		return (ft_env(my_data->all_cmd[my_data->crt], my_data));
	return (-1);
}


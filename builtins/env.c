#include "../minishell.h"

int	ft_env(char	**cmd, t_data *my_data)
{
	(void)cmd;
	if (my_data->env)
		print_all(my_data->env);
	return (0);
}

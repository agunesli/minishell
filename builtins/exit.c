#include "../minishell.h"

int	all_is_digit(char *str)
{
	int	i;

	i = -1;
	if (str[++i] != '-' && str[i] != '+')
		i--;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	ft_exit(char **cmd, t_data *my_data)
{
	int	nb;

	nb = 0;
	if (!cmd[1])
	{
		ft_free_end(my_data);
		exit(g_error);
	}
	else
	{
//	printf("exit\n");
		if (all_is_digit(cmd[1]) && !cmd[2])
		{
			nb = ft_atoi(cmd[1]) % 256;
			ft_free_end(my_data);
			exit(nb);
		}
		else if (all_is_digit(cmd[1]) && cmd[2])
		{
			//printf("bash: exit: too many arguments\n");
			ft_free_end(my_data);
			exit(1);
//			ft_free_necessary(my_data);
		}
		else if (!all_is_digit(cmd[1]))
		{
			//printf("bash: exit: %s: numeric argument required\n", cmd[1]);
			ft_free_end(my_data);
			exit(2);
		}
	}
	return (nb);
}

#include "../minishell.h"

int	ft_pwd(char **cmd, t_data *my_data)
{
	char	buffer_pwd[4096];

	(void)my_data;
	(void)cmd;
	if (getcwd(buffer_pwd, sizeof(buffer_pwd)) != NULL)
		printf("%s\n", buffer_pwd);
	else
	{
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
		return (1);
	}
	return (0);
}

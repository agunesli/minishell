#include "../minishell.h"

void	putstr_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	errorp(char *str)
{
	putstr_error("bash: ");
	putstr_error(str);
	perror(" ");
}

void	error_syntax(char *str, t_data *my_data)
{
	my_data->status_error = 2;
	putstr_error("bash: syntax error near unexpected token ");
	putstr_error(str);
	putstr_error("\n");
}

void	error_command(char *str, t_data *my_data)
{
	my_data->status_error = 2;
	putstr_error("bash: ");
	putstr_error(str);
	putstr_error(": command not found\n");
}

//void	error_execve(char *str, t_data *my_data)

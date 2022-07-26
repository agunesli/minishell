#include "../minishell.h"

void	clean_fd(void)
{
	dup2(STDIN_FILENO, STDIN_FILENO);
	dup2(STDOUT_FILENO, STDOUT_FILENO);
	if (isatty(0))
		printf("YESS\n");
}

void	exec_one_cmd(t_data *my_data, t_syntax *syn)
{
	int status;

	status = is_builtins(my_data);
	if (status)
	{
		g_error = hub_builtins(status, my_data);
		clean_fd();
	}
	else
	{
		update_data_exec(my_data);
		exec(syn, my_data);
		end_of_parent(my_data);
	}
}

void	get_start_exec(t_data *my_data, t_syntax *syn)
{
	if (syn->id >= in)
		exec_one_cmd(my_data, syn);
	else
		exec_with_pipe(my_data, syn);
}

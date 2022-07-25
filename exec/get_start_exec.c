#include "../minishell.h"

void	exec_one_cmd(t_data *my_data, t_syntax *syn)
{
	int built;

	built = is_builtins(my_data); 
	if (built != -1)
		g_error = built;
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

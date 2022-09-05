#include "../minishell.h"

void	clean_fd(int ft_init[2])
{
	dup2(ft_init[0], STDIN_FILENO);
	close(ft_init[0]);
	dup2(ft_init[1], STDOUT_FILENO);
	close(ft_init[1]);
}

void	exec_one_cmd(t_data *my_data, t_syntax *syn)
{
	int	status;

	if (!my_data->all_cmd[my_data->crt])
		return ;
	status = is_builtins(my_data);
	if (status)
	{
//		fd_init[0] = dup(STDIN_FILENO);
//		fd_init[1] = dup(STDOUT_FILENO);
		change_fd(my_data->syn);
		g_error = hub_builtins(status, my_data);
		//ft_free_end(my_data);
		ft_free_necessary(my_data);
//		clean_fd(fd_init);
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
	int	fd_sdt[2];

	fd_sdt[0] = dup(STDIN_FILENO);
	fd_sdt[1] = dup(STDOUT_FILENO);
	if (syn->id >= in)
		exec_one_cmd(my_data, syn);
	else
		exec_with_pipe(my_data, syn);
	clean_fd(fd_sdt);
}

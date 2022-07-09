#include "../minishell.h"

void	start(t_data *my_data)
{
	if (my_data->syn->id == PIPE)
		pipe(my_data);
	else if (my_data->syn->id == OR)
		or(my_data);
	else if (my_data->syn->id == AND)
		and(my_data);
	else if (my_data->syn->id == in || my_data->syn->id == heredoc)
		fdin(my_data);
	else if (my_data->syn->id == out || my_data->syn->id == append)
		fdout(my_data);
	else
		cmd(my_data);
}

void test(uint8_t const ump_index)
{
    void (*pf[])(void) = {echo, cd, pwd, export, unset, env, exit};

    if (jump_index < sizeof(pf) / sizeof(*pf))
    {
        /* Call the function specified by jump_index */
        pf[jump_index]();
    }
}

int	errror(t_data my_data)
{
	perror("bash : %d: ", my_data->status_error); 
}

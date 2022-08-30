/*#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include<wait.h>
#include<signal.h>

#define CYELLOW "\001\e[0;36m\002"
#define RESET   "\001\e[0m\002"
*/
#include "../minishell.h"


int g_error = 0;

int main(int argc, char **argv, char **env)
{
	char	*read;
	t_data	my_data;
//	int		sg;

	(void)argc;
	(void)argv;
	read = NULL;
	signal_def();
//	printf("signal %d\n", sg);
	init_data(&my_data, read, env);
	while (42)
	{
//		if (read)
//			free(read);
		read = readline(CYELLOW "Minishell💙 > " RESET);
//		printf("signal %d\n", sg);
		if (!read)
			exit(0);
		if (read && *read)
		{
//			signal_def();
			add_history(read);
			get_start(&my_data, read);
//			write(1, "bouh\n",5);
		}
	}
	rl_clear_history();
//	free(read);
	return (0);
}

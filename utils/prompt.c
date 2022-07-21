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

int main(int argc, char **argv, char **env)
{
	char	*read;

	(void)argc;
	(void)argv;
//	(void)env;
//	print_all(env);
	read = NULL;
	signal_def();
	while (42)
	{
//		if (read)
//			free(read);
		read = readline(CYELLOW "Minishell💙 > " RESET);
		if (!read)
			exit(0);
		if (read && *read)
		{
			add_history(read);
			get_start(read, argv, env);
//			write(1, "bouh\n",5);
		}
	}
//	free(read);
	return (0);
}

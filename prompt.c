#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "minishell.h"

#define CYELLOW "\001\e[0;36m\002"
#define RESET   "\001\e[0m\002"
int main(int argc, char **argv, char **env)
{
	char	*read;

	(void)argc;
	(void)argv;
	(void)env;
	read = NULL;
	while (42)
	{
		if (read)
			free(read);
		read = readline(CYELLOW "Minishell> " RESET);
		printf("%s", read);
		if (!read)
			exit(0);
		if (read && *read)
			add_history(read);
	}
	free(read);
	return (0);
}

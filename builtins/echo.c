#include "../minishell.h"

/* check -nnnn */
int	check_option_nl(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
//		printf("cmd is %s\n", cmd[i]);
		if (cmd[i][j] == '-' && cmd[i][j + 1] == 'n')
		{
//			printf("HERE\n");
			j++;
			while (cmd[i][j] == 'n')
				j++;
//			printf("j is %d and strlen odf cmd is %ld\n", j, ft_strlen(cmd[i]));
			if (j != (int)ft_strlen(cmd[i]))
				return (i - 1);
		}
		else
			return (i - 1);
	}
	return (-1);
}

int	ft_echo(char **cmd, t_data *my_data)
{
	int	nl;
	int	i;

	(void)my_data;
	print_all(cmd);
	nl = check_option_nl(cmd);
	printf("nl is %d\n", nl);
	i = nl;
	while (cmd[++i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
	}
	if (!nl)
		write(1, "\n", 1);
	return (0);
}
/*
struct s
{
	int size;
	char *str;
	t_token_type
};



void
test ()
{
	static const char* tmp = {	"echo",
								"pwd",
								"exit",
								"cd",
								"export",
								"unset",
								"env"};

}*/

#include "../minishell.h"

char	*bye_esp(char *read)
{
	int		y;
	char	*tmp;

	y = 0;
	while (read[y] == ' ')
		y++;
	tmp = ft_substr(read, y, ft_strlen(read) - y + 1);
	free(read);
	return (tmp);
}

int	check_read(char *read)
{
	int	y;

	y = 0;
	while (read[y] == ' ')
		y++;
	if (!read[y])
		return (1);
	if (read[y] == '\n')
		return (1);
	else if (read[y] == ':')
		return (1);
	else if (read[y] == '!')
		return (1);
	return (0);
}

void	get_start(t_data *my_data, char *read)
{
	if (check_read(read))
		return ;
	my_data->read = bye_esp(read);
	my_data->syntax = 1;
	my_data->syn = NULL;
	my_data->syn = strong_piece(my_data->read, my_data);
	my_data->nb_process = 1;
	my_data->crt = 0;
	if (my_data->syntax)
	{
		check_tree(my_data->syn, my_data);
		if (my_data->syntax)
		{
			print_tree(my_data->syn);
			update_data(my_data);
			get_start_exec(my_data, my_data->syn);
			free_tree(my_data->syn);
			free_tab3(my_data->all_cmd);
		}
	}
}

/*int	main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		printf("Espece de conne tu as oublie les arguments !!\n");
		return (0);
	}
//	(void)ac;
//	(void)av;
//	char *s = "<fd1 ls >fd >fd1 -la <fd1 | ls && << LIM";
//	char *t = "\"\" accher\"$USER\" \"  \"";
//	char *u = "/usr/bin/cat| ls ";
//	printf("\ns = %s\n", s);
//	parser(s, av, env);
//	printf("\nt = %s\n", t);
//	parser(t, av, env);
//	printf("\nu = %s\n", u);
//	parser(u, av, env);
	printf("\nread = [%s]\n", av[1]);
	parser(av[1], av, env);
	return (0);
}*/

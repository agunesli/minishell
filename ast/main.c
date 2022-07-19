#include "../minishell.h"

int	check_read(char *read)
{
	if (!ft_strncmp("\n", read, 1))
			return (1);
/*	else if (!ft_strncmp("\t", read, 1))
			return (1);*/
	else if (!ft_strncmp(":", read, 1))
			return (1);
	else if (!ft_strncmp("!", read, 1))
			return (1);
	return (0);

}

// REFAIRE CETTE FONCTION
void	parser(char *read, char **av, char **env)
{
//	t_syntax	*syn;
	t_data		my_data;

	while (*read == ' ')
		read++;	
	if (!read)
		return ;
	if (check_read(read))
		return ;
	init_data(&my_data, read, av, env);
//	print_tree(my_data.syn);
	if (!my_data.status_error)
	{
		check_tree(my_data.syn, &my_data);
		print_tree(my_data.syn);
		update_data(&my_data);
	//	print_tree(my_data.syn);
	//	change_all_fd(my_data.syn);
		start_exec(&my_data, my_data.syn);
		free_tree(my_data.syn);
		free_tab3(my_data.all_cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
	{
		printf("Espece de conne tu as oublie les arguments !!\n");
		return (0);
	}
//	(void)ac;
//	(void)av;
//	char *s = "<fd1 ls >fd >fd1 -la <fd1 | ls && << LIM"; // SEG FAULT
//	char *s = "<fd1 ls >fd <in -la | echo >out \" bonjour\" <fd \"$USER\" && sleep 3 >in";
//	char *t = "\"\" accher\"$USER\" \"  \"";
//	char *u = "cat < Makefile | cat";
//	printf("\ns = %s\n", s);
//	parser(s, av, env);
//	printf("\nt = %s\n", t);
//	parser(t, av, env);
//	printf("\nu = %s\n", u);
//	parser(u, av, env);
	printf("\nread = [%s]\n", av[1]);
	parser(av[1], av, env);
	return (0);
}

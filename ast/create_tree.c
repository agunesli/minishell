#include "../minishell.h"

t_syntax	*low_piece(char *subread, t_data *my_data) //cmd
{
 	t_syntax	*syn;

	if (!subread)
 		return (NULL);
	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = cmd;
	syn->cmd_arg = parse_cmd(subread, my_data);
	syn->content = NULL;
	syn->right = NULL;
	syn->left = NULL;
//	free(subread);
	return (syn);
}

t_syntax	*medium_piece(char *subread, t_data *my_data)
{
	t_syntax	*syn;
	int			i;

	if (!subread)
		return (NULL);
	i = good_place(subread, MEDIUM, 0);
	if (i == (int)ft_strlen(subread))
		syn = low_piece(ft_substr(subread, 0, end_sub(subread, ft_strlen(subread))), my_data);
	else
	{
		if (subread[i] == '<')
			syn = redirection_in(subread, i, my_data);
		else
			syn = redirection_out(subread, i, my_data);
	}
	free(subread);
	return (syn);
}

// arg malloc pour eviter pb avec free lors du premier lancement
t_syntax	*strong_piece(char *read, t_data *my_data) 
{
	t_syntax	*syn;
	int			i;
	int			start;
	char		*str;

	if (!read)
 		return (NULL);
	i = good_place(read, STRONG, 0);
	if (i == (int)ft_strlen(read))
		syn = medium_piece(ft_strdup(read), my_data);
	else
	{
		syn = malloc(sizeof(t_syntax));
		if (!syn)
			return (NULL);
		syn->content = NULL;
		syn->cmd_arg = NULL;
		if (read[i] == '|' && read[i + 1] != '|')
			syn->id = PIPE;
		else if (read[i] == '|' && read[i + 1] == '|')
			syn->id = OR;
		else if (read[i] == '&' && read[i + 1] == '&')
			syn->id = AND;
		/*else // cas ou un seul & mais je ne connais pas le comportement !
			sym->id = error*/
		syn->left = medium_piece(ft_substr(read, 0, end_sub(read, i)), my_data);
		if (syn->id == PIPE)
			start = skip_space(read, i + 1);
		else
			start = skip_space(read, i + 2);
		str = ft_substr(read, start, end_sub(read, ft_strlen(read)) - start);
		syn->right = strong_piece(str, my_data);
	}
	free(read);
//	print_tree(syn);
	return (syn);
}

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

void	free_tree(t_syntax *syn)
{
	if (!syn)
		return ;
//	printf("free %s\n", syn->content);
	free(syn->content); 
	free_all(syn->cmd_arg); 
	free_tree(syn->left);
	free_tree(syn->right);
	free(syn);
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
	if (!my_data.status_error)
		check_tree(my_data.syn, &my_data);
	print_tree(my_data.syn);
	update_data(&my_data);
//	print_tree(my_data.syn);
	change_all_fd(my_data.syn);
	free_tree(my_data.syn);
	free_tab3(my_data.all_cmd);
}

int	main(int ac, char **av, char **env)
{
/*	if (ac == 1)
	{
		printf("Espece de conne tu as oublie les arguments !!\n");
		return (0);
	}*/
	(void)ac;
	(void)av;
//	char *s = "<fd1 ls >fd >fd1 -la <fd1 | ls && << LIM"; // SEG FAULT
	char *s = "<fd1 ls >fd <in -la | echo >out \" bonjour\" <fd \"$USER\" && sleep 3 >in";
//	char *t = "\"\" accher\"$USER\" \"  \"";
//	char *u = ">>>>>";
	printf("\ns = %s\n", s);
	parser(s, av, env);
//	printf("\nt = %s\n", t);
//	parser(t, av, env);
//	printf("\nu = %s\n", u);
//	parser(u, av, env);
//	printf("\nread = [%s]\n", av[1]);
//	parser(av[1], av, env);
	return (0);
}

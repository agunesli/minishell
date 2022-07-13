#include "../minishell.h"

t_syntax	*low_piece(char *subread, t_data *my_data) //cmd
{
 	t_syntax	*syn;

	if (!subread)
 		return (NULL);
// 	printf("subread[0] is [%c]\n", subread[0]);
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
	char		*str;

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
/*		else // cas ou un seul & mais je ne connais pas le comportement !
			sym->*/
		syn->left = medium_piece(ft_substr(read, 0, skip_space(read, i)), my_data);
		if (syn->id == PIPE)
			str = ft_substr(read, skip_space(read, i + 1), ft_strlen(read));
		else
			str = ft_substr(read, skip_space(read, i + 2), ft_strlen(read));
		syn->right = strong_piece(str, my_data);
	}
	free(read);
//	print_tree(syn);
	return (syn);
}

void	free_tree(t_syntax *syn)
{
	if (!syn)
		return ;
	printf("free %s\n", syn->content);
	free(syn->content); //all
	free_all(syn->cmd_arg); //all
	free_tree(syn->left);
	free_tree(syn->right);
	free(syn);
}

// REFAIRE CETTE FONCTION
void	parser(char *read, char **env)
{
	t_syntax	*syn;
	t_data		my_data;

	while (*read == ' ')
		read++;	
	my_data.read = read;
	my_data.env = env;
	syn = strong_piece(ft_strdup(my_data.read), &my_data);
	my_data.syn = &syn;
	print_tree(syn);
	free_tree(syn);

/*	syn = strong_piece(ft_strdup(read));
	print_tree(syn);*/
	// create fonction print
/*	t_syntax *syn;
	int	x;

	x = found_strong_piece(read);
	if (x == -1)
		syn = medium_piece(read, x); // fonction a faire
	sym->content = NULL;
	if (read[x] == '&')
		syn->id = AND;
	else if (read[x] == '|' && read[x + 1] == '|')
		syn->id = OR;
	else
		syn->id = pipe;
	syn->left = found_medium_piece(ft_substr(read, 0, x));*/
	//reflechir pour bien positionner pour la recursion
}

int	main(int ac, char **av, char **env)
{
	errno = 0;
/*	if (ac == 1)
	{
		printf("Espece de conne tu as oublie les arguments !!\n");
		return (0);
	}*/
	(void)ac;
	(void)av;
	char *s = "ls$CC";
	char *t = "\"\" accher\"$USER\" \"  \"";
	char *u = "\"\" \'accher$USER\' \"  \"";
	printf("s = %s\n", s);
	parser(s, env);
	printf("\nt = %s\n", t);
	parser(t, env);
	printf("\nu = %s\n", u);
	parser(u, env);
//	parser(av[1]);
	return (0);
}

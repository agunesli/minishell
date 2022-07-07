#include "../minishell.h"

// cmd
// star
// single quote
// double quote
// $
// $?
t_syntax	*low_piece(char *subread) //cmd
{
 	t_syntax	*syn;

 	if (!subread)
 		return (NULL);
	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = cmd;
	syn->content = subread;
	syn->right = NULL;
	syn->left = NULL;
	return (syn);
}


t_syntax	*medium_piece(char *subread)
{
	t_syntax	*syn;
	int			i;

	if (!subread)
		return (NULL);
	i = good_place(subread, MEDIUM, 0);
	if (i == (int)ft_strlen(subread))
		syn = low_piece(ft_substr(subread, 0, end(subread, ft_strlen(subread))));
	else
	{
		if (subread[i] == '<')
			syn = redirection_in(subread, i);
		else
			syn = redirection_out(subread, i);
	}
	free(subread);
	return (syn);
}

// arg malloc pour eviter pb avec free lors du premier lancement
t_syntax	*strong_piece(char *read) 
{
	t_syntax	*syn;
	int			i;
	char		*str;

	i = good_place(read, STRONG, 0);
	if (i == (int)ft_strlen(read))
		syn = medium_piece(ft_strdup(read));
	else
	{
		syn = malloc(sizeof(t_syntax));
		if (!syn)
			return (NULL);
		syn->content = NULL;
		if (read[i] == '|' && read[i + 1] != '|')
			syn->id = PIPE;
		else if (read[i] == '|' && read[i + 1] == '|')
			syn->id = OR;
		else if (read[i] == '&' && read[i + 1] == '&')
			syn->id = AND;
/*		else // cas ou un seul & mais je ne connais pas le comportement !
			sym->*/
		syn->left = medium_piece(ft_substr(read, 0, skip_space(read, i)));
		if (syn->id == PIPE)
			str = ft_substr(read, skip_space(read, i + 1), ft_strlen(read));
		else
			str = ft_substr(read, skip_space(read, i + 2), ft_strlen(read));
		syn->right = strong_piece(str);
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
	free(syn->content);
	free_tree(syn->left);
	free_tree(syn->right);
	free(syn);
}

// REFAIRE CETTE FONCTION
void	parser(char *read)
{
	t_syntax *syn;

	while (*read == ' ')
		read++;	
	syn = strong_piece(ft_strdup(read));
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

int	main(int ac, char **av)
{
	(void)ac;
//	(void)av;
//	char *s = "<< LIM cmd1 | cmd2 >> file2";
//	parser(s);
	parser(av[1]);
	return (0);
}

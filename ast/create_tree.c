#include "../minishell.h"

// cmd
// star
// single quote
// double quote
// $
// $?
int	len_arg(char *cmd)
{
	int		i;
	int		cpt;
	char	c;

	i = -1;
	cpt = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			while (cmd[++i] && cmd[i] != c)
				;
			if (cmd[i])
				cpt+=2;
			else
				return (-1);
		}
	}
	return (cpt);
}

char	*without_quote(char *cmd)
{
	int		cpt;
	char	*dest;
	int		i;
	int		j;
	char	c;

	cpt = len_arg(cmd);
	i = ((j = -1, -1));
//	if (cpt == -1)
//		error ?
	if (cpt == 0)
		return (cmd);
	dest = malloc(sizeof(char) * (ft_strlen(cmd) - cpt + 1));
	if (!dest)
		return (NULL);
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			while(cmd[++i] && cmd[i] != c)
				dest[++j] = cmd[i];
		}
		else
				dest[++j] = cmd[i];
	}
	dest[j] = '\0';
	free(cmd);
	return (dest);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	tmp2 = ft_strjoin(tmp1, s3);
	free(s3);
	free(tmp1);
	return (tmp2);
}

char	*found_word_expand(char *subread, int i)
{
	int	len;
	int	j;

	j = i - 1;
	len = 0;
	while (subread[++j] != ' ' && subread[j] != '\"')
		len++;
	return (ft_substr(subread, i, len));
}

char	*expand_error(char *expand, t_data *my_data)
{
	char	*dst;
	char	*tmp1;
	char	*tmp2;

	if (expand[1] == ' ' || expand[1] == '\n')
		return (ft_itoa(my_data->status_error));
	tmp1 = ft_itoa(my_data->status_error);
	tmp2 = ft_substr(expand, 1, ft_strlen(expand));
	dst = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (dst);
}

char	*found_expand(char *expand, t_data *my_data)
{
	int	i;

	i = -1;	
	if (!ft_strncmp(expand, "?", 1))
		return (expand_error(expand, my_data));
	while (my_data->env[++i] != NULL)
	{
		if (!ft_strncmp(expand, my_data->env[i], ft_strlen(expand)))
			return (ft_strdup(env + ft_strlen(expand) + 1))
	}
	return (NULL); //Cas d'erreur !!
}

char	*change_expand(char *cmd, int i, t_data *my_data)
{
	char	*part1;
	char	*part2;
	char	*expand;
	char	*result;
	int		start2;

	part1 = ft_substr(cmd, 0, i);
	expand = found_word_expand(cmd, i + 1);
	start2 = i + ft_strlen(expand) + 1;
	part2 = ft_substr(cmd, start2, ft_strlen(cmd) - start2);
	result = found_expand(expand, my_data);
	free(cmd);
	free(expand)
	return (ft_strjoin3(part1, result, part2));
}

// A FAIRE QUE ENTRE "" 
char	*expand(char *cmd, t_data *my_data)
{
	int	i;
	int	qoute;

	i = -1;
	quote = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\"')
			quote = -quote;
		else if (cmd[i] == '$' && quote)
			cmd = change_expand(cmd, i, my_data);
	}
	return (cmd);
//	if (!cmd[i])
//	else if (cmd[i + 1] == '?' && quote)
//		return (ft_itoa(my_data->status_error));
//	else
//		return (change_expand(cmd, i, my_data));
}

// = $ ~ * "'
char	**parse_cmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != NULL)
	{
		cmd[i] = expand(cmd[i], my_data);
		cmd[i] = without_quote(cmd[i]);
	}
}

t_syntax	*low_piece(char *subread, t_data my_data) //cmd
{
 	t_syntax	*syn;

 	if (!subread)
 		return (NULL);
	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = cmd;
	syn->cmd_arg = parse_cmd(ft_split(subread, ' '), my_data);
	syn->content = NULL;
	syn->right = NULL;
	syn->left = NULL;
	return (syn);
}

t_syntax	*medium_piece(char *subread, t_data my_data)
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
t_syntax	*strong_piece(char *read, t_data my_data) 
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
	free_tree(syn->left);
	free_tree(syn->right);
	free(syn);
}

// REFAIRE CETTE FONCTION
void	parser(char *read)
{
	t_syntax	*syn;
	t_data		my_data;

	while (*read == ' ')
		read++;	
	my_data.read = read;
	syn = strong_piece(ft_strdup(my_data.read), my_data);
	my_data = &syn;
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
	errno = 0;
	(void)ac;
//	(void)av;
//	char *s = "<< LIM cmd1 | cmd2 >> file2";
//	parser(s);
	parser(av[1]);
	return (0);
}

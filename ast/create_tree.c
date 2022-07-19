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
	syn->cmd_arg = change_cmd(subread, my_data);
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

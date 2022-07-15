#include "../minishell.h"

char	*without_nl(char *src)
{
	char	*dest;

	dest = ft_substr(src, 0, ft_strlen(src) - 1);
	free(src);
	return (dest);
}

void	write_more(t_syntax *syn, t_data *my_data)
{
	char	*line;

	write(1, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (!ft_strncmp(line, "\n", 1))
	{
		free(line);
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	line = without_nl(line);
	syn->right = strong_piece(line, my_data);
}

void	check_open(char *name, int opt)
{
	int fd;

	fd = open_file(name, opt);
	close(fd);
}

void	check_strong(t_syntax *syn, t_data *my_data)
{
	if (syn->left == NULL)
	{
		if (syn->id == OR)
			return(error_syntax("\'||\'", my_data));
		else if (syn->id == AND)
			return(error_syntax("\'&&\'", my_data));
		else if (syn->id == PIPE)
			return(error_syntax("\'|\'", my_data));
	}
	else if (syn->left->id == in || syn->left->id == append 
		|| syn->left->id == heredoc)
		return(error_syntax("\'|\'", my_data));
	else if (syn->left->id == out)
		return ;
	if (syn->right == NULL)
		write_more(syn, my_data);
}

void	check_medium(t_syntax *syn, t_data *my_data)
{
	if (syn->left != NULL && in <= syn->left->id && syn->left->id <= append)
	{
		if (syn->left->id == in)
			return(error_syntax("\'<\'", my_data));
		if (syn->left->id == out)
			return(error_syntax("\'>\'", my_data));
		if (syn->left->id == heredoc)
			return(error_syntax("\'<<\'", my_data));
		if (syn->left->id == append)
			return(error_syntax("\'>>\'", my_data));
	}
	if (!syn->content)
		return(error_syntax("\'newline\'", my_data));
	else if (syn->content && syn->id != heredoc)
		check_open(syn->content, syn->id);
}
/*
void	check_low(t_syntax *syn, t_data *my_data)
{

}*/

void	check_tree(t_syntax *syn, t_data *my_data/*, int i*/)
{
	if (!syn)
		return ;
	if (syn->id == PIPE || syn->id == AND || syn->id == OR)
		check_strong(syn, my_data);
	else if (in <= syn->id && syn->id <= append)
		check_medium(syn, my_data);
	/*else
		check_low(syn, my_data);*/
	if (my_data->status_error)
		return ;
	check_tree(syn->left, my_data);
	check_tree(syn->right, my_data);
}
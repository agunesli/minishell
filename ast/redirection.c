#include "../minishell.h"

char	*found_name_fd(char *subread, int y)
{
	int	i;
	//A tester sur le shell et trouve les cas d'erreur 
	i = 0;
	while (subread[y] == ' ')
		y++;
	i = y;
	while (subread[y] && subread[y] != ' ' && subread[y] != '\n'
			&& subread[y] != '>' && subread[y] != '<')
		y++;
	return (ft_substr(subread, i, y - i));
}

t_syntax	*ft_heredoc(char *subread, int y, t_data *my_data)
{
	t_syntax	*syn;
//	int			i;
	int			start;
	char		*tmp;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
//	i = write_heredoc(subread, y);
	syn->id = heredoc;
	syn->cmd_arg = NULL;
//	syn->content = ft_strdup("~/tmp/.here_doc");
	syn->content = write_heredoc(subread, y);
	tmp = found_name_fd(subread, y);
	start = skip_space(subread, ft_strlen(tmp) + y + 1);
	free(tmp);
	syn->right = low_piece(ft_substr(subread, start, ft_strlen(subread)), my_data);
	syn->left = low_piece(ft_substr(subread, skip_space(subread, 0), end_sub(subread, y - 2)), my_data);
	return (syn);
}

int	end_sub(char *subread, int len)
{
	while (subread[len - 1] == ' ')
		len--;
	return (len);
}

t_syntax	*change_std(char *subread, int y, int id, t_data *my_data)
{
	t_syntax	*syn;
	int		start;
	int		end;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = id;
	syn->cmd_arg = NULL;
	syn->content = found_name_fd(subread, y);
	if (y != 1)
	{	
		syn->left = low_piece(ft_substr(subread, 0, y - 1), my_data);
	//	start = skip_space(subread, y + ft_strlen(syn->content) + 1);
		start = skip_space(subread, skip_space(subread, y) + ft_strlen(syn->content));
		end = end_sub(subread, ft_strlen(subread));
		syn->right = medium_piece(ft_substr(subread, start, end), my_data);
	}
	else
	{
		start = skip_space(subread, skip_space(subread, y) + ft_strlen(syn->content) + 1);
//		end = end_sub(subread, ft_strlen(subread));
		syn->left = medium_piece(ft_substr(subread, start, ft_strlen(subread)), my_data);
		syn->right = NULL;
	}
	return (syn);
}

t_syntax	*redirection_in(char *subread, int y, t_data *my_data)
{
	t_syntax	*syn;

	if (subread[y] == '<' && subread[y + 1] == '<')
		syn = ft_heredoc(subread, y + 2, my_data);
	else
	//	else if (subread[y] == '<' && subread[y + 1] != '<')
		syn = change_std(subread, y + 1, in, my_data);
	return (syn);
}

t_syntax	*redirection_out(char *subread, int y, t_data *my_data)
{
	t_syntax	*syn;

	if (subread[y] == '>' && subread[y + 1] == '>')
		syn = change_std(subread, y + 2, append, my_data);
	else
//	else if (subread[y] == '>' && subread[y + 1] != '>')
		syn = change_std(subread, y + 1, out, my_data);
	return (syn);
}

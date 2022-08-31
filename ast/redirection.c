#include "../minishell.h"

char	*found_name_fd(char *subread, int y)
{
	int	i;

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
	int			start;
	int			end;
	char		*tmp;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = heredoc;
	syn->cmd_arg = NULL;
	syn->content = create_heredoc(subread, y, my_data);
	if (syn->content == NULL)
		return (free(syn), NULL);
	start = skip_space(subread, 0);
	end = end_sub(subread, y - 2);
	syn->left = low_piece(ft_substr(subread, start, end), my_data);
	tmp = found_name_fd(subread, y);
	start = skip_space(subread, ft_strlen(tmp) + y + 1);
	free(tmp);
	end = ft_strlen(subread) - start;
	syn->right = medium_piece(ft_substr(subread, start, end), my_data);
	return (syn);
}

t_syntax	*handle_std(char *subread, int y, int id, t_data *my_data)
{
	t_syntax	*syn;
	int			start;
	int			end;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = id;
	syn->cmd_arg = NULL;
	syn->content = found_name_fd(subread, y);
	start = skip_space(subread, skip_space(subread, y));
	start += ft_strlen(syn->content);
	if (y == 1 || (y == 2 && id == append))
	{
//		start = skip_space(subread, skip_space(subread, y);
//		start += ft_strlen(syn->content));
		end = ft_strlen(subread);
		syn->right = medium_piece(ft_substr(subread, start, end), my_data);
		syn->left = NULL;
	}
	else
	{
		if (id == append)
			syn->left = low_piece(ft_substr(subread, 0, y - 2), my_data);
		else
			syn->left = low_piece(ft_substr(subread, 0, y - 1), my_data);
//		start = skip_space(subread, skip_space(subread, y) + ft_strlen(syn->content));
		end = end_sub(subread, ft_strlen(subread));
		syn->right = medium_piece(ft_substr(subread, start, end), my_data);
	}
	return (syn);
}

t_syntax	*redirection_in(char *subread, int y, t_data *my_data)
{
	t_syntax	*syn;

	if (subread[y] == '<' && subread[y + 1] == '<')
		syn = ft_heredoc(subread, y + 2, my_data);
	else
		syn = handle_std(subread, y + 1, in, my_data);
	return (syn);
}

t_syntax	*redirection_out(char *subread, int y, t_data *my_data)
{
	t_syntax	*syn;

	if (subread[y] == '>' && subread[y + 1] == '>')
		syn = handle_std(subread, y + 2, append, my_data);
	else
		syn = handle_std(subread, y + 1, out, my_data);
	return (syn);
}

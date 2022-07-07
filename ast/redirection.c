#include "../minishell.h"

char	*found_name_fd(char *subread, int y)
{
	int	i;
	//A tester sur le shell et trouve les cas d'erreur 
	i = 0;
	while (subread[y] == ' ')
		y++;
	i = y;
	while (subread[y] != ' ' && subread[y] != '\n')
		y++;
	return (ft_substr(subread, i, y - i));
}

t_syntax	*ft_heredoc(char *subread, int y)
{
	t_syntax	*syn;
	int			i;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	i = write_heredoc(subread, y);
	syn->id = heredoc;
	syn->content = ft_strdup("~/tmp/.here_doc");
	syn->left = low_piece(ft_substr(subread, skip_space(subread, i + y + 1), ft_strlen(subread)));
	syn->right = NULL;
	return (syn);
}

int	end(char *subread, int len)
{
	while (subread[len - 1] == ' ')
		len--;
	return (len);
}


t_syntax	*change_std(char *subread, int y, int id)
{
	t_syntax	*syn;
	int		start;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = id;
	syn->content = found_name_fd(subread, y);
	if (syn->id == in)
	{
		start = skip_space(subread, y) +  ft_strlen(syn->content) + 1;
		syn->left = low_piece(ft_substr(subread, start, end(subread, ft_strlen(subread))));
	}
	else if (syn->id == out)
		syn->left = low_piece(ft_substr(subread, 0, end(subread, y - 1)));
	else
		syn->left = low_piece(ft_substr(subread, 0, end(subread, y - 2)));
	syn->right = NULL;
	return (syn);
}

t_syntax	*redirection_in(char *subread, int y)
{
	t_syntax	*syn;

	if (subread[y] == '<' && subread[y + 1] == '<')
		syn = ft_heredoc(subread, y + 2);
	else
	//	else if (subread[y] == '<' && subread[y + 1] != '<')
		syn = change_std(subread, y + 1, in);
	return (syn);
}

t_syntax	*redirection_out(char *subread, int y)
{
	t_syntax	*syn;

	if (subread[y] == '>' && subread[y + 1] == '>')
		syn = change_std(subread, y + 2, append);
	else
//	else if (subread[y] == '>' && subread[y + 1] != '>')
		syn = change_std(subread, y + 1, out);
	return (syn);
}

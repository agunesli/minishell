#include "minishell.h"

char	*found_name_fd(char *read, int y)
{
	int	i;
	//A tester sur le shell et trouve les cas d'erreur 
	while (read[y] == ' ')
		y++;
	i = y;
	while (read[i] != ' ' || read[i] != '\n')
		i++;
	return (ft_substr(read, y, i));
}

t_syntax	*ft_heredoc(char *subread, int y, char *read)
{
	t_syntax	*syn;
	int			i;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	i = write_heredoc(subread, y, read);
	syn->id = heredoc;
	syn->content = ft_strdup("~/tmp/.here_doc");
	syn->right = NULL;
	syn->left = low_piece(ft_substr(subread, skip_space(subread, i), ft_strlen(subread)));
	return (syn);
}

t_syntax	*change_std(char *read, int y, int id)
{
	t_syntax	*syn;
	int		start;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = id;
	syn->content = found_name_fd(read, y);
	syn->right = NULL;
	start = skip_space(subread, y) +  ft_strlen(syn->content);;
	syn->left = low_piece(ft_substr(subread, start, ft_strlen(subread)));
	return (syn);
}

t_syntax	*redirection_in(char *subread, int y, char *read)
{
	t_syntax	*syn;

	if (subread[y] == '<' && subread[y + 1] == '<')
		syn = ft_heredoc(subread, y + 2, read);
	else if (subread[y] == '<' && subread[y + 1] != '<')
		syn = change_std(subread, y + 2, in);
	return (syn);
}

t_syntax	*redirection_out(char *read, int y, char *read)
{
	t_syntax	*syn;

	if (read[y] == '>' && read[y + 1] == '>')
		syn = change_std(read, y + 2, append);
	else if (read[y] == '>' && read[y + 1] != '>')
		syn = change_std(read, y + 2, out);
	return (syn);
}

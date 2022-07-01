#include "minishell.h"

char	*found_name_fd(char *read)
{
	int	i;
	//A tester sur le shell et trouve les cas d'erreur 
	while (*read == ' ')
		read++;
	while (read[i] != ' ' || read[i] != '\n')
		i++;
	return (ft_substr(read, 0, i));
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
	syn->left = NULL;
	syn->right = low_piece(ft_substr(subread, skip_space(subread, i), ft_strlen(subread)));
	return (syn);
}

t_syntax	*change_std(char *read, int id)
{
	t_syntax *syn;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = id;
	syn->content = found_name_fd(read);
	syn->left = NULL;
	syn->right = low_piece(ft_substr(subread, skip_space(subread, i), ft_strlen(subread)));
	return (syn);
	return (syn);
}

t_syntax	*redirection_in(char *subread, int y, char *read)
{
	t_syntax	*syn;

	if (subread[y] == '<' && subread[y + 1] == '<')
		syn = ft_heredoc(subread, y + 2, read);
	else if (subread[y] == '<' && subread[y + 1] != '<')
		syn = change_std(subread + 1, in);
	return (syn);
}

t_syntax	*redirection_out(char *read, int y, char *read)
{
	t_syntax	*syn;

	if (read[y] == '>' && read[y + 1] == '>')
		syn = change_std(read + 1, append);
	else if (read[y] == '>' && read[y + 1] != '>')
		syn = change_std(read + 1, out);
	return (syn);
}

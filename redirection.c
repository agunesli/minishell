#include "minishell.h"

t_syntax	*heredoc(char *subread, char *read)
{
	int			fd;
	t_syntax	*syn;

	write_heredoc(subread, read);
	syn->id = heredoc;
	syn->content = ft_strdup("~/tmp/.here_doc");
	syn->left = NULL;
	syn->right = NULL;
	return (syn)
}

char	*found_name_fd(char *read, int opt)
{
	int	i;
	//A tester sur le shell et trouve les cas d'erreur 
	while (*read == ' ')
		read++;
	if (opt = in)
	{
		while (read[i] != ' ')
			i++;
		return (ft_substr(read, 0, i));
	}
	while (read[i] != ' ' || read[i] != '\n')
		i++;
	return (ft_substr(read, 0, i));
}

// 0 => in, 1 => out, 2 => append
t_syntax	*change_std(char *read, int opt)
{
	syn->id = opt;
	syn->content = found_name_fd(read, opt);
	syn->left = NULL;
	syn->right = NULL;
	return (syn);
}

t_syntax	*redirection_in(char *subread, int y, char *read)
{
	if (subread[y] == '<' && subread[y + 1] == '<')
		return(heredoc(read + y + 2, read));
	else if (read[y] == '<' && read[y + 1] != '<')
		return (change_std(read + y + 1, in));
}

t_syntax	*redirection_out(char *read, int y)
{
	if (read[y] == '>' && read[y + 1] == '>')
		return (change_std(read + y + 1, append));
	else if (read[y] == '>' && read[y + 1] != '>')
		return (change_std(read + y + 1, out));
}

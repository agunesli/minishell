#include "../minishell.h"

t_syntax	*low_piece(char *subread, t_data *my_data)
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
	return (syn);
}

t_syntax	*medium_piece(char *subread, t_data *my_data)
{
	t_syntax	*syn;
	int			i;
	int			end;

	if (!subread)
		return (NULL);
	i = good_place(subread, MEDIUM, 0, my_data);
	if (i < 0)
		return (NULL);
	if (i == (int)ft_strlen(subread))
	{
		end = end_sub(subread, ft_strlen(subread));
		syn = low_piece(ft_substr(subread, 0, end), my_data);
	}
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
	i = good_place(read, STRONG, 0, my_data);
	if (i < 0)
		return (NULL);
	if (i == (int)ft_strlen(read))
	{
		syn = medium_piece(ft_strdup(read), my_data);
	}
	else
	{
		syn = malloc(sizeof(t_syntax));
		if (!syn)
			return (NULL);
		syn->id = PIPE;
		syn->content = ((syn->cmd_arg = NULL, NULL));
		syn->left = medium_piece(ft_substr(read, 0, end_sub(read, i)), my_data);
		start = skip_space(read, i + 1);
		str = ft_substr(read, start, end_sub(read, ft_strlen(read)) - start);
		syn->right = strong_piece(str, my_data);
	}
	return (free(read), syn);
}
//	free(read);

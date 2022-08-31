/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:21:18 by agunesli          #+#    #+#             */
/*   Updated: 2022/08/31 18:25:13 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_syntax	*handle_std_next(t_syntax *syn, char *subrd, int y, t_data *my_data)
{
	int			end;
	int			start;

	start = skip_space(subrd, skip_space(subrd, y));
	start += ft_strlen(syn->content);
	if (y == 1 || (y == 2 && syn->id == append))
	{
		end = ft_strlen(subrd);
		syn->right = medium_piece(ft_substr(subrd, start, end), my_data);
		syn->left = NULL;
	}
	else
	{
		if (syn->id == append)
			syn->left = low_piece(ft_substr(subrd, 0, y - 2), my_data);
		else
			syn->left = low_piece(ft_substr(subrd, 0, y - 1), my_data);
		end = end_sub(subrd, ft_strlen(subrd));
		syn->right = medium_piece(ft_substr(subrd, start, end), my_data);
	}
	return (syn);
}

t_syntax	*handle_std(char *subread, int y, int id, t_data *my_data)
{
	t_syntax	*syn;

	syn = malloc(sizeof(t_syntax));
	if (!syn)
		return (NULL);
	syn->id = id;
	syn->cmd_arg = NULL;
	syn->content = found_name_fd(subread, y);
	return (handle_std_next(syn, subread, y, my_data));
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

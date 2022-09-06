/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:42:55 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 20:42:56 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_fd(t_syntax *syn, t_data *my_data)
{
	int	fd;

	if (!syn)
		return ;
	if (syn->id == in || syn->id == heredoc)
	{
		fd = open_file(syn->content, syn->id);
		if (fd == -1)
			ft_free_necessary(my_data);
		dup2(fd, STDIN_FILENO);
		close(fd);
		change_fd(syn->right, my_data);
	}
	else if (syn->id == out || syn->id == append)
	{
		fd = open_file(syn->content, syn->id);
		if (fd == -1)
			ft_free_necessary(my_data);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		change_fd(syn->right, my_data);
	}
}

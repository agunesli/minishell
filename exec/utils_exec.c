/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:52:59 by tamather          #+#    #+#             */
/*   Updated: 2022/09/07 09:05:11 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_split(char **bin)
{
	int	i;

	i = 0;
	while (bin[i])
		i++;
	return (i);
}

int	open_file(char *file, int i, t_data *my_data)
{
	int	fd;

	fd = 0;
	if (i == in || i == heredoc)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			errorp(file, my_data);
			return (-1);
		}
	}
	else if (i == out)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (i == append)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		errorp(file, my_data);
	return (fd);
}

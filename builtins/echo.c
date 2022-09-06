/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:29:52 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 18:30:03 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option_nl(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
		if (cmd[i][j] == '-' && cmd[i][j + 1] == 'n')
		{
			j++;
			while (cmd[i][j] == 'n')
				j++;
			if (j != (int)ft_strlen(cmd[i]))
				return (i);
		}
		else
			return (i);
	}
	return (i);
}

int	ft_echo(char **cmd, t_data *my_data)
{
	int	nl;
	int	i;

	(void)my_data;
	nl = check_option_nl(cmd);
	i = nl;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!(nl - 1))
		write(1, "\n", 1);
	return (0);
}

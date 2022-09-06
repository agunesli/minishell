/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:24:41 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 18:24:42 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	print_all(char **bin)
{
	int	i;

	i = -1;
	if (bin == NULL)
	{
		ft_putstr("NULL\n");
		return ;
	}
	while (bin[++i] != NULL)
	{
		ft_putstr(bin[i]);
		ft_putstr("\n");
	}
}

int	found_char(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int	id_check(char *str, int i)
{
	int	len;
	int	j;

	j = -1;
	if (i == -1)
		len = ft_strlen(str);
	else
		len = i;
	if (str[0] && ft_isdigit(str[0]))
		return (0);
	while (str[++j] && j < len)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
	}
	return (1);
}

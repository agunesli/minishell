/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:24:20 by agunesli          #+#    #+#             */
/*   Updated: 2022/07/23 14:17:43 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] == '\f') || (str[i] == '\n')
		|| (str[i] == '\r') || (str[i] == '\t') || (str[i] == '\v'))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;
	int		nb_;

	nb = 0;
	nb_ = 1;
	i = ft_isspace(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			nb_ = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * nb_);
}

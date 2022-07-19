/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:06:36 by agunesli          #+#    #+#             */
/*   Updated: 2022/07/19 10:46:11 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_size_nb(long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*dst;
	long	nb;

	nb = n;
	len = ft_size_nb(nb);
	dst = (char *)malloc(sizeof(char) *(len + 1));
	if (!dst)
		return (NULL);
	if (nb == 0)
		dst[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		dst[0] = '-';
	}
	dst[len] = '\0';
	while (nb > 0)
	{
		len--;
		dst[len] = (nb - (nb / 10) * 10) + '0';
		nb /= 10;
	}
	return (dst);
}

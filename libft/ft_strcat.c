/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:46:45 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 20:46:47 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_strcat(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst + strlen(dst);
	while (*src != '\0')
	{
		ptr++ = src++;
	}
	*ptr = '\0';
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:26:26 by agunesli          #+#    #+#             */
/*   Updated: 2022/08/31 18:28:02 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_arg(char *cmd)
{
	int		i;
	int		cpt;
	char	c;

	i = -1;
	cpt = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			while (cmd[++i] && cmd[i] != c)
				;
			if (cmd[i])
				cpt += 2;
		}
	}
	return (cpt);
}

char	*without_quote(char *cmd)
{
	int		cpt;
	char	*dest;
	int		i;
	int		j;
	char	c;

	cpt = len_arg(cmd);
	i = ((j = -1, -1));
	if (cpt == 0)
		return (cmd);
	if (cpt == (int)ft_strlen(cmd))
		return (free(cmd), ft_strdup(""));
	dest = malloc(sizeof(char) * (ft_strlen(cmd) - cpt + 1));
	if (!dest)
		return (NULL);
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			while (cmd[++i] && cmd[i] != c)
				dest[++j] = cmd[i];
		}
		else
				dest[++j] = cmd[i];
	}
	dest[++j] = '\0';
	return (free(cmd), dest);
}

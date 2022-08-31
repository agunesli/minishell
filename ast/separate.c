/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:35:04 by agunesli          #+#    #+#             */
/*   Updated: 2022/08/31 18:12:48 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**separate_word(char *cmd, char **dest, int cpt, t_data *my_data)
{
	int		i;
	int		len;
	int		j;

	i = 0;
	j = -1;
	if (!cpt)
		dest[++j] = ft_strdup(cmd);
	else
	{
		while (cmd && cmd[i])
		{
			while (cmd[i] && cmd[i] == ' ')
				i++;
			len = good_place(cmd, " ", i, my_data) - i;
			dest[++j] = ft_substr(cmd, i, len);
			i += len;
		}
	}
	dest[++j] = NULL;
	free(cmd);
	return (dest);
}

int	cpt_good_space(char *cmd)
{
	int		cpt;
	char	c;
	int		i;

	i = ((cpt = 0, -1));
	while (++i < (int)ft_strlen(cmd) && cmd[i])
	{
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\'' && cmd[i] != '\"')
			i++;
		c = cmd[i];
		if (c == '\'' || c == '\"')
		{
			i++;
			while (cmd[i] && cmd[i] != c)
				i++;
		}
		else if (c == ' ')
		{
			while (cpt++ && cmd[i] && cmd[i] == c && cmd[i + 1] != '\''
				&& cmd[i + 1] != '\"')
				i++;
		}
	}
	return (cpt);
}

char	**separate(char *cmd, t_data *my_data)
{
	int		cpt;
	char	**dest;

	cpt = cpt_good_space(cmd);
	dest = malloc(sizeof(char *) * (cpt + 2));
	if (!dest)
		return (NULL);
	return (separate_word(cmd, dest, cpt, my_data));
}

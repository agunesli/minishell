/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunesli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:00:58 by agunesli          #+#    #+#             */
/*   Updated: 2022/07/22 13:01:01 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**change_str_to_tab(char *str)
{
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * 2);
	if (!dst)
		return (NULL);
	dst[0] = ft_strdup(str);
	dst[1] = NULL;
	return (dst);
}

char	**ft_tabdup(char **src)
{
	char	**dst;
	int		i;

	if (!src)
		return (NULL);
	i = -1;
	dst = malloc(sizeof(char *) * (len_split(src) + 1));
	if (!dst)
		return (NULL);
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	return (dst);
}

char	**ft_strjointab(char **s1, char **s2)
{
	char	**dst;
	int		j;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = -1;
	j = -1;
	dst = malloc(sizeof(char *) * (len_split(s1) + len_split(s2) + 1));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = ft_strdup(s1[i]);
	while (s2[++j])
		dst[i + j] = ft_strdup(s2[j]);
	dst[i + j] = NULL;
	free_all(s1);
	free_all(s2);
	return (dst);
}

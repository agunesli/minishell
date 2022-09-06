/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:27:06 by agunesli          #+#    #+#             */
/*   Updated: 2022/09/06 18:36:42 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*found_word(char *subread, int i)
{
	int	len;
	int	j;

	j = i - 1;
	len = 0;
	while (subread[++j] && subread[j] != ' ' && subread[i] != '\n')
		len++;
	return (ft_substr(subread, i, len));
}

int	end_sub(char *subread, int len)
{
	if (len < 1)
		return (0);
	while (len > 0 && subread[len - 1] == ' ')
		len--;
	return (len);
}

int	skip_space(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	good_place(char *read, char *set, int i, t_data *my_data)
{
	char	c;

	while (read[i] && !ft_is_in_set(read[i], set)
		&& read[i] != '\'' && read[i] != '\"')
		i++;
	c = read[i];
	if (c == '\'' || c == '\"')
	{
		i++;
		while (read[i] && read[i] != c)
			i++;
		if (!read[i])
		{
			free(read);
			if (c == '\'')
				error_syntax("\'", my_data);
			else
				error_syntax("\"", my_data);
			return (-1);
		}
		return (good_place(read, set, i + 1, my_data));
	}
	else
		return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:29:47 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 18:29:48 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char	**cmd, t_data *my_data)
{
	(void)cmd;
	if (my_data->env)
		print_all(my_data->env);
	return (0);
}

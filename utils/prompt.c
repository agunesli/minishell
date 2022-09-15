/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:22:10 by tamather          #+#    #+#             */
/*   Updated: 2022/09/15 10:59:09 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_error = 0;

int	main(int argc, char **argv, char **env)
{
	char	*read;
	t_data	my_data;

	(void)argc;
	(void)argv;
	read = NULL;
	signal_def();
	init_data(&my_data, read, env);
	while (42)
	{
		read = readline(CYELLOW "Minishell💙 > " RESET);
		if (!read)
		{
			ft_free_end(&my_data);
			exit(g_error);
		}
		if (read && *read)
		{
			add_history(read);
			get_start(&my_data, read);
		}
	}
	rl_clear_history();
	return (0);
}

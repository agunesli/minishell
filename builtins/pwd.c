/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:20:47 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 18:24:32 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **cmd, t_data *my_data)
{
	char	buffer_pwd[4096];

	(void)my_data;
	(void)cmd;
	if (getcwd(buffer_pwd, sizeof(buffer_pwd)) != NULL)
		printf("%s\n", buffer_pwd);
	else
	{
		putstr_error("pwd: error retrieving current directory: ");
		perror("getcwd: cannot access parent directories");
		return (1);
	}
	return (0);
}

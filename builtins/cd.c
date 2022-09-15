/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:30:10 by tamather          #+#    #+#             */
/*   Updated: 2022/09/15 11:15:24 by agunesli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**update_oldpwd_in_env(char **env, char *old_pwd)
{
	int		i;
	char	*tmp1;
	char	**tmp2;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("OLDPWD=", env[i], 7))
			break ;
	}
	if (env[i])
	{
		free(env[i]);
		env[i] = ft_strjoin("OLDPWD=", old_pwd);
	}
	else
	{
		tmp1 = ft_strjoin("OLDPWD=", old_pwd);
		tmp2 = change_str_to_tab(tmp1);
		env = ft_strjointab(env, tmp2);
		free(tmp1);
	}
	return (env);
}

char	**update_pwd_in_env(char **env, char *pwd)
{
	int		i;
	char	*tmp1;
	char	**tmp2;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("PWD=", env[i], 4))
			break ;
	}
	if (env[i])
	{
		free(env[i]);
		env[i] = ft_strjoin("PWD=", pwd);
	}
	else
	{
		tmp1 = ft_strjoin("PWD=", pwd);
		tmp2 = change_str_to_tab(tmp1);
		env = ft_strjointab(env, tmp2);
		free(tmp1);
	}
	return (env);
}

char	*change_oldpwd(char old_pwd[4096], char *dst)
{
	if (*old_pwd)
	{
		ft_strlcat(old_pwd, "/", 4096);
		ft_strlcat(old_pwd, dst, 4096);
		return (ft_strdup(old_pwd));
	}
	else
		return (ft_strdup(""));
}

/* Tu dois update tes vars denv avec le old path sur 
OLDPWD, des le debut, puisque si x == 1, old_pwd sera modif */
int	ft_cd_handler(char *dst, t_data *my_data, int x)
{
	char	old_pwd[4096];
	char	*final_path;
	int		rtvl;

	final_path = ((rtvl = 0, NULL));
	old_pwd[0] = 0;
	getcwd(old_pwd, sizeof(old_pwd));
	my_data->env = update_oldpwd_in_env(my_data->env, old_pwd);
	if (x == 0)
		final_path = ft_strjoin(getenv("HOME"), dst + 1);
	else if (x == 1)
		final_path = change_oldpwd(old_pwd, dst);
	else
		final_path = ft_strdup(dst);
	if (chdir(final_path) == -1)
	{
		cd_error(dst);
		rtvl = 1;
	}
	else
		my_data->env = update_pwd_in_env(my_data->env, old_pwd);
	free(final_path);
	free(dst);
	return (rtvl);
}

/* first case : relative paths */
/* second case : no backslash */
/* third case : correct format */
int	ft_cd(char **cmd, t_data *my_data)
{
	char	*dst_path;
	int		rtvl;

	if (cmd[1] == NULL)
		return (1);
	dst_path = strdup(cmd[1]);
	if (dst_path[0] == '~')
		rtvl = ft_cd_handler(dst_path, my_data, 0);
	else if (dst_path[0] != '/')
		rtvl = ft_cd_handler(dst_path, my_data, 1);
	else
		rtvl = ft_cd_handler(dst_path, my_data, 2);
	return (rtvl);
}

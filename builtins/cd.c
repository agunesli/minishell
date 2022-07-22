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
		printf("srjyjr\n");
		tmp1 = ft_strjoin("OLDPWD=", old_pwd);
		tmp2 = change_str_to_tab(tmp1);
		env = ft_strjointab(env, tmp2);
		free(tmp1);
		free_all(tmp2);
	}
	return (env);
}

void cd_error(char *str)
{
	fprintf(stderr, "bash: cd: %s: No such file or directory", str);
}

/* Tu dois update tes vars denv avec le old path sur OLDPWD, des le debut, puisque si x == 1, old_pwd sera modif */
int ft_cd_handler(char *dst, t_data *my_data, int x)
{
	char old_pwd[4096];
	char *final_path;
	int rtvl;

	final_path = ((rtvl = 0, NULL));
	getcwd(old_pwd, sizeof(old_pwd));
	my_data->env = update_oldpwd_in_env(my_data->env, old_pwd);
	if (x == 0)
		final_path = ft_strjoin(getenv("HOME"), dst + 1);
	else if (x == 1)
	{
		strcat(old_pwd, "/");
		strcat(old_pwd, dst);
		final_path = ft_strdup(old_pwd);
	}
	else
		final_path = ft_strdup(dst);
	if (chdir(final_path) == -1)
	{
		cd_error(dst);
		rtvl = -1;
	}
	free(final_path);
	free(dst);
	return (rtvl);
}

/* first case : relative paths */
/* second case : no backslash */
/* third case : correct format */
int ft_cd(char **cmd, t_data *my_data)
{
	char	*dst_path;
	char	actual[4096];
	int 	rtvl;

	if (cmd[1] == NULL)
	{
		return -1;
	}
	dst_path = strdup(cmd[1]);
	if (dst_path[0] == '~')
	{
		rtvl = ft_cd_handler(dst_path, my_data, 0);
	}
	else if (dst_path[0] != '/')
	{
		rtvl =  ft_cd_handler(dst_path, my_data, 1);
	}
	else
	{
		rtvl = ft_cd_handler(dst_path, my_data, 2);
	}
	printf("ACTUAL POS : %s \n", getcwd(actual, sizeof(actual)));
	return rtvl;
}

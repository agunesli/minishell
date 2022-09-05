#include "../minishell.h"

void	start_env(char **env, t_data *my_data)
{
	char	buffer_pwd[4096];

	if (env[0] == NULL)
	{
		my_data->env = malloc(sizeof(char *) * 4);
		if (!my_data->env)
			return ;
		my_data->env[0] = ft_strjoin("PWD=",
				getcwd(buffer_pwd, sizeof(buffer_pwd)));
		my_data->env[1] = ft_strdup("SHLVL=1");
		my_data->env[2] = ft_strdup("_=/usr/bin/env");
		my_data->env[3] = NULL;
		my_data->path = ft_strdup("PATH=/mnt/nfs/homes/agunesli/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/mnt/nfs/homes/agunesli/.local/bin");
	}
	else
		my_data->env = ft_tabdup(env);
}

void	init_data(t_data *my_data, char *read, char **env)
{
	my_data->read = read;
	my_data->path = NULL;
	my_data->env = NULL;
	my_data->exprt = NULL;
	start_env(env, my_data);
	my_data->nb_process = 1;
	my_data->crt = 0;
	my_data->all_cmd = NULL;
	my_data->syn = NULL;
	my_data->childs = NULL;
}

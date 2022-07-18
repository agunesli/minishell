#include "minishell.h"

int	nb_strong_piece(t_syntax *syn, int cpt)
{
	if (PIPE <= syn->id && syn->id <= AND)
		return (nb_strong_piece(syn->right, cpt + 1));
	else
		return (cpt);
}

char	**handle_cmd(t_syntax *syn, char **cmd1)
{
	char	**tmp;

	if (!syn)
		return (cmd1);
	if (in <= syn->id && syn->id <= append)
	{
		if (syn->left)
		{
			tmp = ft_strjointab(cmd1, ft_tabdup(syn->left->cmd_arg));
			return (handle_cmd(syn->right, tmp));
		}
		return (handle_cmd(syn->right, cmd1));
	}
	else if (syn->id == cmd)
		return (ft_strjointab(cmd1, ft_tabdup(syn->cmd_arg)));
	return (cmd1);
}

char	***handle_all_cmd(t_data *my_data, t_syntax *syn)
{
	char	***all_cmd;
	int		i;

	i = -1;
	all_cmd = malloc(sizeof(char **) * (my_data->nb_process + 1));
	if (!all_cmd)
		return (NULL);
	while (syn->id < in)
	{
		all_cmd[++i] = handle_cmd(syn->left, NULL);
		print_all(all_cmd[i]); //
		syn = syn->right;
	}
	all_cmd[++i] = handle_cmd(syn, NULL);
	print_all(all_cmd[i]); //
	all_cmd[++i] = NULL;
//	printf("i in handlecmd is %d\n", i); //
	return (all_cmd);
}

void	update_data(t_data *my_data)
{
	my_data->nb_process = nb_strong_piece(my_data->syn, 0) + 1;
	printf("nb process is %d\n", my_data->nb_process); //
	my_data->all_cmd = handle_all_cmd(my_data, my_data->syn); //need to be free
}

void	init_data(t_data *my_data, char *read, char **av, char **env)
{
	my_data->read = read;
	my_data->argv = av;
	my_data->env = env;
	my_data->status_error = 0;
	my_data->nb_process = 1;
	my_data->current_process = 0;
	my_data->path = NULL;
	my_data->all_cmd = NULL; //need to be free
	my_data->syn = strong_piece(ft_strdup(read), my_data);
}


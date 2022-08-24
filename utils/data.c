#include "../minishell.h"

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
		syn = syn->right;
	}
	all_cmd[++i] = handle_cmd(syn, NULL);
	all_cmd[++i] = NULL;
	return (all_cmd);
}

void	update_data(t_data *my_data)
{
	my_data->nb_process = nb_strong_piece(my_data->syn, 0) + 1;
	my_data->all_cmd = NULL;
	my_data->all_cmd = handle_all_cmd(my_data, my_data->syn); //need to be free
}

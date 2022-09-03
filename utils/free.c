#include "../minishell.h"

void	free_all(char **bin)
{
	int	i;

	i = -1;
	if (!bin)
		return ;
	while (bin[++i])
		free(bin[i]);
//	printf("free all i = %d\n", i);
	free(bin);
}

void	free_tab3(char ***bin)
{
	int	i;

	i = -1;
	if (!bin)
		return ;
	while (bin[++i])
	{
//		print_all(bin[i]);
		free_all(bin[i]);
	}
	free(bin);
}

void	free_tree(t_syntax *syn)
{
	if (!syn)
		return ;
//	printf("free %s\n", syn->content);
	if(syn->content)
	{
		free(syn->content);
		syn->content = NULL;
	}
	if (syn->cmd_arg)
	{
		free_all(syn->cmd_arg);
		syn->cmd_arg = NULL;
	}
	if (syn->left)
	{
		free_tree(syn->left);
		syn->left = NULL;
	}
	if (syn->right)
	{
		free_tree(syn->right);
		syn->right = NULL;
	}
	free(syn);
	syn = NULL;
}

void	ft_free_end(t_data *my_data)
{
	if (my_data->syn)
		free_tree(my_data->syn);
//	if (my_data->childs)
//		free(my_data->childs);
	if (my_data->all_cmd)
	{
		free_tab3(my_data->all_cmd);
		my_data->all_cmd = NULL;
	}
	free_all(my_data->env);
	free(my_data->path);
}

void	ft_free_necessary(t_data *my_data)
{
	if(my_data->syn)
		free_tree(my_data->syn);
	if(my_data->childs)
	{ 
		free(my_data->childs);
		my_data->childs = NULL;
	}
	if (my_data->all_cmd)
	{
		free_tab3(my_data->all_cmd);
		my_data->all_cmd = NULL;
	}
}

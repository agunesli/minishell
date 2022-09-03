#include "../minishell.h"

void	free_all(char **bin)
{
	int	i;

	i = -1;
	if (!bin)
		return ;
	while (bin[++i])
		free(bin[i]);
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
	t_syntax	*tmp1;
	t_syntax	*tmp2;
	
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
	tmp1 = syn->left;
	tmp2 = syn->right;
	free(syn);
	free_tree(tmp1);
	free_tree(tmp2);
/*	if (syn)
	{
		printf("bouhhh\n");
		free(syn);
		syn = NULL;
		printf("2 %p\n", syn);
	}*/
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
	{
		free_tree(my_data->syn);
		my_data->syn = NULL;
	}
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

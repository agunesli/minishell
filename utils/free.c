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
	free(syn->content); 
	free_all(syn->cmd_arg); 
	free_tree(syn->left);
	free_tree(syn->right);
	free(syn);
}

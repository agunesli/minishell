#include "../minishell.h"

int	g_current_level;


void	print_syn(char *item, int id, char **cmd, int current_level)
{
	int	i;

	i = -1;
	printf("[%d] ID is %d and content is {%s} ", current_level, id, item);
	if (cmd)
	{
		printf("cmd is ");
		while (cmd[++i] != NULL)
			printf("{%s} ", cmd[i]);
		printf("\n");
	}
	else
		printf("\n");
}

int	max2(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

int	btree_level_count2(t_syntax *root)
{
	if (!root)
		return (0);
	return (max2(btree_level_count2(root->left),
			btree_level_count2(root->right)) + 1);
}

void	apply(t_syntax *root,
			void (*applyf)(char *item, int id, char **cmd, int current_level),
			int level)
{
	if (!root)
		return ;
	if (level > g_current_level)
		return ;
	if (level == g_current_level)
	{
		applyf(root->content, root->id, root->cmd_arg, level);
		return ;
	}
	apply(root->left, applyf, level + 1);
	apply(root->right, applyf, level + 1);
}

void	btree_apply_by_level(t_syntax *root,
	void (*applyf)(char *item, int id, char **cmd, int current_level))
{
	int	count;
	int	level;

	count = btree_level_count2(root);
	level = 0;
	while (level < count)
	{
		g_current_level = level;
		level++;
		apply(root, applyf, 0);
	}
}

void	print_tree(t_syntax *syn)
{
	btree_apply_by_level(syn, &print_syn);
}

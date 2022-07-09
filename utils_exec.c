#include "minishell.h"

void	free_all(char **bin)
{
	int	i;

	i = 0;
	while (bin[i])
	{
		free(bin[i]);
		i++;
	}
	free(bin);
}

void	free_all_int(int **bin, int nb_process)
{
	int	i;

	i = 0;
	while (i < nb_process)
	{
		free(bin[i]);
		i++;
	}
	free(bin);
}

int	open_file(char *file, int i)
{
	if (i == 1)
		return (open(file, O_RDONLY));
	else if (i == 2)
		return (open(file, O_CREAT | O_RDWR | O_TRUNC, 0644));
	else if (i == 3)
		return(open(file, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

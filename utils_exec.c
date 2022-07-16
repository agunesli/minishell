#include "minishell.h"

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

int	len_split(char **bin)
{
	int	i;

	i = 0;
	while (bin[i])
		i++;
	return (i);
}

int	open_file(char *file, int i)
{
	int	fd;

	fd = 0;
	if (i == in || i == heredoc)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			errorp(file); //[1] bash: name_file: No such file or directory
			return (-1);
		}
	}
	else if (i == out)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (i == append)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror(""); //a modifie !!
	//	printf("bash: name_file: Permission denied\n"); //[1] bash: name_file: Permission denied 
	return (fd);
}

#include "../minishell.h"

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
		errorp(file); //a modifie !!
	//	printf("bash: name_file: Permission denied\n"); //[1] bash: name_file: Permission denied 
	return (fd);
}

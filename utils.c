#include "minishell.h"

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

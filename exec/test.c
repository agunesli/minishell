#include "../minishell.h"

//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
int	*childs(t_data *my_data)
{
	int	*childs;
	int	i;

	i = -1;
	childs = malloc(sizeof(int) * my_data->nb_process);
	if (!childs)
		return (NULL);
	while (++i < my_data->nb_process)
	{
			
	}
}

void	exec(t_data my_data)
{
	int fds[2][2];
	int	*childs;

	if (pipe(fds[0]) == -1)
		printf("Error\n");
	if (pipe(fds[1]) == -1)
		printf("Error\n");

}

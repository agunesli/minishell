
#include "pipex.h"

void	parent(int **fds, int *childs, int nb_process)
{
	int	i;

	i = 0;
	while (i < nb_process)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	free_all_int(fds, nb_process);
	i = 0;
	while (i < nb_process)
	{
		waitpid(childs[i], NULL, 0); // recuperer sa valeur de retourn pour && ou ||
										// et les cas d'erreur !!
		i++;
	}
	free(childs);
}

t_cmd	create_t_cmd(t_donnee *don, int i)
{
	t_cmd	sc;

	if (don->here_doc)
	{
		sc.cmd_arg = ft_split(don->argv[i + 3], ' ');
		sc.path = correct_path(don->argv[i + 3], don->env, sc.cmd_arg);
	}
	else
	{
		sc.cmd_arg = ft_split(don->argv[i + 2], ' ');
		sc.path = correct_path(don->argv[i + 2], don->env, sc.cmd_arg);
	}
	return (sc);
}

void	not_execve(t_donnee *don, int *childs, t_cmd *scmd, int i)
{
	free_all(scmd->cmd_arg);
	free(scmd->path);
	free(childs);
	if (close(don->fds[i][0]) == -1)
		merror("Error with close\n");
	if (close(don->fds[i + 1][1]) == -1)
		merror("Error with close\n");
	free_all_int(don->fds, don->nb_process);
	merror("Error with execve\n");
}

int	*create_childs(t_donnee *don)
{
	int		*childs;
	int		i;
	t_cmd	scmd;

	childs = (int *)malloc(sizeof(int) * don->nb_process); /// Bien compter le nb process
	if (!childs)
		merror("Error with malloc childs\n");
	i = -1;
	while (syn->right->id != PIPE)
	{
		childs[i] = fork();
		if (childs[i] == -1)
			merror("Error with fork child\n");
		if (childs[i] == 0)
		{
			close_fds(don->fds, don->nb_process, i); // refaire cette fonction
			ft_dup2(don->fds, i, don->nb_process, don->argv);
			scmd = create_t_cmd(don, i);
			if (execve(scmd.path, scmd.cmd_arg, don->env) == -1)
				not_execve(don, childs, &scmd, i);
		}
		if (don->here_doc && i == 0)
			waitpid(childs[0], NULL, 0);
	}
	return (childs);
}


//fork() => child process = 0 else main process
//pipe() => fd[0] = read, fd[1] = write
//execve => v = array, e = env (Error = -1)
//nb_process => argc - 3 car fdint, fdout, pipex
int	main(int argc, char **argv, char **env)
{
	int			**fds;
	int			*childs;
	int			here_doc;
	int			nb_process;
	t_donnee	donnee;

	fds = create_fds(nb_process);
	childs = create_childs(&donnee);
	parent(fds, childs, nb_process);
	return (0);
}

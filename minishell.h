#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

enum e_syntax
{
	pipe,
	OR,
	AND,
	in,
	out,
	heredoc,
	append
};

typedef struct	s_syntax
{
	int id;
	char *content;
	struc s_syntax left;
	struc s_syntax right;
}	t_syntax;

int	found_char(char *read, char c);
int	ft_min(int x, int y, int z);

//parser
t_syntax	*rediction_in(char *read, int y);
t_syntax	*rediction_out(char *read, int y);

//libft
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);


#endif

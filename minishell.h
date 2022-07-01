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

# define STRONG "|&"
# define MEDIUM "<>"
# define LOW "$*"

typedef void (*sighandler_t)(int);

enum e_syntax
{
	PIPE,
	OR,
	AND,
	in,
	out,
	heredoc,
	append,
	cmd,
	expand,
	star,
	error
};

typedef struct	s_syntax
{
	int				id;
	char			*content;
	struct s_syntax	*left;
	struct s_syntax	*right;
}	t_syntax;

typedef struct s_data
{
	t_syntax	**syn;
	char		**env;
	int			error;
}	t_data;

int			found_char(char *read, char c);
int			ft_is_in_set(char c, const char *set);
int			skip_space(char *str, int i);
//parser
t_syntax	*redirection_in(char *read, int y);
t_syntax	*redirection_out(char *read, int y);
t_syntax	*low_piece(char *subread, char *read);

//utils
int	open_file(char *file, int i);

//libft
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
#endif

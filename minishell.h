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
#include <errno.h>

# define STRONG "|&"
# define MEDIUM "<>"
# define LOW "\"\'$*"

typedef void (*sighandler_t)(int);

enum e_syntax
{
	PIPE,	// 0
	OR,	// 1
	AND,	// 2
	in,	// 3
	out,	// 4
	heredoc,// 5
	append,	// 6
	cmd,	// 7
	dollar, // 8
	star,	// 9
	error	// 10
};

typedef struct	s_syntax
{
	int				id;
	char			*content;
	char			**cmd_arg;
	struct s_syntax	*left;
	struct s_syntax	*right;
}	t_syntax;

typedef struct s_data
{
	char		*read;
	char		**argv;
	char		**env;
	t_syntax	*syn;
	int			nb_process;
	char		***all_cmd;
	int			status_error;
}	t_data;

int			found_char(char *read, char c);

//data
void		init_data(t_data *my_data, char *read, char **av, char **env);
void		update_data(t_data *my_data);

//parser
t_syntax	*redirection_in(char *read, int y, t_data *my_data);
t_syntax	*redirection_out(char *read, int y, t_data *my_data);
t_syntax	*low_piece(char *subread, t_data *my_data);
t_syntax	*medium_piece(char *subread, t_data *my_data);
t_syntax	*strong_piece(char *read, t_data *my_data);
char		*write_heredoc(char *subread, int y, t_data *my_data);
void		print_tree(t_syntax *syn);
char		**separate(char *cmd);
char		**parse_cmd(char *cmd, t_data *my_data);
char		*expand(char *cmd, t_data *my_data);
char		*without_quote(char *cmd);
void		check_tree(t_syntax *syn, t_data *my_data);
void		error_syntax(char *str, t_data *my_data);
void		error_command(char *str, t_data *my_data);
void		errorp(char	*str);

//utils_tree
int			ft_is_in_set(char c, const char *set);
char	*found_word(char *subread, int i);
char	*found_word_star(char *subread, int i);
int			skip_space(char *str, int i);
int			good_place(char *read, char *set, int i);
int			end_sub(char *subread, int len);
char		*ft_strjoin3(char *s1, char *s2, char *s3);

//utils_exec
int	open_file(char *file, int i);
void	free_all_int(int **bin, int nb_process);
void	free_all(char **bin);
void	print_all(char **bin);
int		len_split(char **bin);

//libft
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2); //GNL utils
char	*ft_substr_end(char const *s, unsigned int start, size_t end);  //GNL utils
char	*ft_itoa(int n); 
char	**ft_strjointab(char **s1, char **s2);

#endif

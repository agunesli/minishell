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
#include <wait.h>
#include <errno.h>

//# define STRONG "|&"
# define STRONG "|"
# define MEDIUM "<>"
# define LOW "\"\'$*"

//couleur pour le prompt
#define CYELLOW "\001\e[0;36m\002"
#define RESET   "\001\e[0m\002"

//# define PATH

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
};

typedef struct	s_syntax
{
	int				id;
	char			*content;
	char			**cmd_arg;
	struct s_syntax	*left;
	struct s_syntax	*right;
}	t_syntax;

//crt = current_process
typedef struct s_data
{
	char		*read;
	char		**argv;
	char		**env;
	char		**exprt;
	t_syntax	*syn; //need to free
	int			nb_process;
	int			crt;
	int			*childs; //need to free
	int			fd[2][2];
	char		***all_cmd; //need to free
	int			status_error;
	char		*path; //NUll sauf si le path n'hesiste pas au debut
}	t_data;

/***********************************************/
/*                  AST                        */
/***********************************************/

// void		get_start(char *read, char **av, char **env);
void		get_start(t_data *my_data, char *read);

//create_tree
t_syntax	*low_piece(char *subread, t_data *my_data);
t_syntax	*medium_piece(char *subread, t_data *my_data);
t_syntax	*strong_piece(char *read, t_data *my_data);

//redirection
t_syntax	*redirection_in(char *read, int y, t_data *my_data);
t_syntax	*redirection_out(char *read, int y, t_data *my_data);
char		*write_heredoc(char *subread, int y, t_data *my_data);

//utils_tree
int			ft_is_in_set(char c, const char *set);
char		*found_word(char *subread, int i);
int			skip_space(char *str, int i);
int			good_place(char *read, char *set, int i, t_data *my_data);
int			end_sub(char *subread, int len);
void		print_tree(t_syntax *syn);

//for cmd
char		**separate(char *cmd, t_data *my_data);
char		**change_cmd(char *cmd, t_data *my_data);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
char		*expand(char *cmd, t_data *my_data);
char		*without_quote(char *cmd);

// check_tree
void		check_tree(t_syntax *syn, t_data *my_data);
char		*without_nl(char *src);
void		write_more(t_syntax *syn, t_data *my_data);
void		check_open(char *name, int opt);


/***********************************************/
/*                  EXEC                       */
/***********************************************/

void		start_exec(t_data *my_data, t_syntax *syn);
void		good_fd(t_syntax *syn, t_data *data);
char		*correct_path(char **cmd, t_data *my_data);

//utils_exec
int			open_file(char *file, int i);
void		print_all(char **bin);
int			len_split(char **bin);

/***********************************************/
/*                 utils                       */
/***********************************************/

//data
void		init_data(t_data *my_data, char *read, char **av, char **env);
void		update_data(t_data *my_data);
void		start_env(char **env, t_data *my_data);

//free
void		free_all(char **bin);
void		free_tab3(char ***bin);
void		free_tree(t_syntax *syn);

// error
void		error_syntax(char *str, t_data *my_data);
void		error_command(char *str, t_data *my_data);
void		errorp(char	*str);

//signal
void		signal_def(void);
void		signal_exec(int pid);

//builtins
int			ft_echo(char **cmd, t_data *my_data);
int			ft_cd(char **cmd, t_data *my_data);
int			ft_pwd(char **cmd, t_data *my_data);
int			ft_env(char **cmd, t_data *my_data);
int			ft_unset(char **cmd, t_data *my_data);
int			ft_export(char **cmd, t_data *my_data);
int			ft_exit(char **cmd, t_data *my_data);

//builtins utils
void		change_env(t_data *my_data, char **dst, int len);
void		change_exprt(t_data *my_data, char **dst;

//libft
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *src);
char		**ft_tabdup(char **src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2); //GNL utils
char		*ft_substr_end(char const *s, unsigned int start, size_t end);  //GNL utils
char		*ft_itoa(int n);
char		**ft_strjointab(char **s1, char **s2);
char		**ft_tabdup(char **src);
char		**change_str_to_tab(char *str);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamather <tamather@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:45:27 by tamather          #+#    #+#             */
/*   Updated: 2022/09/06 20:45:48 by tamather         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <wait.h>
# include <errno.h>

//# define STRONG "|&"
# define STRONG "|"
# define MEDIUM "<>"
# define LOW "\"\'$*"

//couleur pour le prompt
# define CYELLOW "\1\e[0;36m\2"
# define RESET   "\1\e[0m\2"
# define PATH1 "PATH=/mnt/nfs/homes/agunesli/bin:/usr/local/sbin:"
# define PATH2 "/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:"
# define PATH3 "/usr/local/games:/snap/bin:/mnt/nfs/homes/agunesli/.local/bin"

//# define PATH

extern int	g_error;
//typedef void (*sighandler_t)(int);

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
};
enum e_built
{
	b_echo = 1,
	b_cd,
	b_pwd,
	b_exprt,
	b_unset,
	b_env,
	b_exit
};

typedef struct s_syntax
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
	char		**env;
	char		**exprt;
	t_syntax	*syn;
	int			nb_process;
	int			crt;
	int			*childs;
	int			fd_tmp;
	char		***all_cmd;
	int			syntax;
	char		*path;
}	t_data;

/***********************************************/
/*                  AST                        */
/***********************************************/

void		get_start(t_data *my_data, char *read);

//create_tree
t_syntax	*low_piece(char *subread, t_data *my_data);
t_syntax	*medium_piece(char *subread, t_data *my_data);
t_syntax	*strong_piece(char *read, t_data *my_data);

//redirection
t_syntax	*redirection_in(char *read, int y, t_data *my_data);
t_syntax	*redirection_out(char *read, int y, t_data *my_data);
char		*create_heredoc(char *subread, int y, t_data *my_data);

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
char		*expand(char *cmd, t_data *my_data, int i);
char		*change_expand(char *cmd, int i, t_data *my_data);
char		*without_quote(char *cmd);

// check_tree
void		check_tree(t_syntax *syn, t_data *my_data);
char		*without_nl(char *src);
void		write_more(t_syntax *syn, t_data *my_data);
void		check_open(char *name, int opt, t_data *my_data);
char		*found_name_fd(char *subread, int y);

/***********************************************/
/*                  EXEC                       */
/***********************************************/

void		get_start_exec(t_data *my_data, t_syntax *syn);
void		good_fd(t_syntax *syn, t_data *data);
void		change_fd(t_syntax *syn, t_data *my_data);
void		change_pipe(t_data *my_data);
char		*correct_path(char **cmd, t_data *my_data);
int			is_builtins(t_data *my_data);
int			hub_builtins(int opt, t_data *my_data);

//exec
void		exec(t_syntax *syn, t_data *my_data);
void		update_data_exec(t_data *my_data);
void		end_of_parent(t_data *my_data);
void		exec_with_pipe(t_data *my_data, t_syntax *syn);

//utils_exec
int			open_file(char *file, int i);
void		print_all(char **bin);
int			len_split(char **bin);

/***********************************************/
/*                 utils                       */
/***********************************************/

//data
void		init_data(t_data *my_data, char *read, char **env);
void		update_data(t_data *my_data);
void		start_env(char **env, t_data *my_data);

//free
void		free_all(char **bin);
void		free_tab3(char ***bin);
void		free_tree(t_syntax **syn);
void		ft_free_end(t_data *my_data);
void		ft_free_necessary(t_data *my_data);

// error
void		putstr_error(char *str);
void		error_syntax(char *str, t_data *my_data);
void		error_command(char *str, t_data *my_data);
void		errorp(char	*str);
int			error_invalid_id(char *str);

//signal
void		signal_def(void);
void		signal_exec(int pid);
void		sg_heredoc(int sig);
void		signal_ctrbs(int sig);

//builtins
int			ft_echo(char **cmd, t_data *my_data);
int			ft_cd(char **cmd, t_data *my_data);
int			ft_pwd(char **cmd, t_data *my_data);
int			ft_env(char **cmd, t_data *my_data);
int			ft_unset(char **cmd, t_data *my_data);
int			ft_export(char **cmd, t_data *my_data);
int			ft_exit(char **cmd, t_data *my_data);

//builtins utils
int			id_check(char *str, int i);
int			found_char(char *str, char c);
void		change_env(t_data *my_data, char **dst, int len);
void		change_exprt(t_data *my_data, char **dst);

//libft
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *src);
char		**ft_tabdup(char **src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_next_line(int fd);
char		*ft_strjoin(char const *s1, char const *s2); //GNL utils
char		*ft_substr_end(char const *s, unsigned int start, size_t end);
char		*ft_itoa(int n);
char		**ft_strjointab(char **s1, char **s2);
char		**ft_tabdup(char **src);
char		**change_str_to_tab(char *str);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_atoi(const char *str);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
#endif

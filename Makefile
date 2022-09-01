SRC	= libft/ft_split.c libft/ft_substr.c libft/ft_strncmp.c\
	  libft/ft_strdup.c libft/ft_strlen.c libft/ft_itoa.c\
	  libft/ft_strjointab.c libft/ft_isalnum.c libft/ft_atoi.c\
	  libft/get_next_line.c libft/get_next_line_utils.c libft/ft_strrchr.c\
	  ast/create_tree.c ast/redirection.c ast/heredoc.c\
	  ast/check_tree.c ast/low_case.c ast/expand.c\
	  ast/quote.c ast/separate.c ast/get_start.c\
	  ast/utils_tree.c ast/print_tree.c ast/utils_check.c\
	  exec/fd.c exec/utils_exec.c exec/path.c\
	  exec/exec.c exec/exec_builtins.c exec/get_start_exec.c\
	  utils/data.c utils/free.c utils/errors.c\
	  utils/prompt.c utils/signal.c utils/data_init.c\
	  builtins/echo.c builtins/cd.c builtins/pwd.c\
	  builtins/env.c builtins/unset.c builtins/export.c\
	  builtins/exit.c builtins/export_change.c builtins/utils_builtins.c \

SRC_H	= minishell.h

OBJ	= $(SRC:%.c=%.o)

NAME	=	minishell
CC		=	gcc
FLAGS	=	-g3 -Wall -Wextra -Werror #-fsanitize=address 
RM		=	rm -rf
LFLAGS	=	-lreadline #-fsanitize=address

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

$(NAME):$(OBJ) $(SRC_H)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

all:	$(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean
	make all

.PHONY:		all clean fclean bonus re

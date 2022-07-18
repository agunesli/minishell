SRC	= ft_split.c ft_substr.c ft_strncmp.c ft_strdup.c ft_strlen.c ft_itoa.c \
	  ft_strjointab.c\
	  exec/change_fd.c exec/test.c exec/path.c\
	  ast/create_tree.c ast/redirection.c ast/heredoc.c ast/check_tree.c\
	  ast/low_case.c ast/expand.c ast/quote.c ast/errors.c\
	  ast/separate.c ast/utils_tree.c ast/print_tree.c\
	  get_next_line.c get_next_line_utils.c utils_exec.c data.c\

SRC_H	= minishell.h

OBJ	= $(SRC:%.c=%.o)

NAME	=	minishell
CC		=	gcc
FLAGS	=	-g3 -Wall -Wextra -Werror
RM		=	rm -rf

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

$(NAME):$(OBJ) $(SRC_H)
	$(CC) $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean bonus re

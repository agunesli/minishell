SRC	= ft_split.c ft_substr.c ft_strncmp.c ft_strdup.c ft_strlen.c \
	  heredoc.c redirection.c create_tree.c utils_tree.c print_tree.c\
	  get_next_line.c get_next_line_utils.c utils.c \

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

SRC =	src/pipex.c \
		src/utils.c \
		src/split.c \
		src/ft_calloc.c \
		src/pipex_utils.c \
		src/ft_put.c

BONUS_SRC =	src/ft_put.c \
			src/utils.c \
			src/ft_calloc.c \
			src/split.c \
			src/pipex_utils.c \
			bonus/pipex_bonus.c \
			bonus/get_next_line.c \
			bonus/pipex_bonus_utils.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

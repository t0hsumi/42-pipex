NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG = # -g -fsanitize=address

SRCS = ft_pipex.c ft_split.c ft_utils.c
OBJS = $(SRCS:.c=.o)

B_SRCS = ft_pipex_bonus.c
B_OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re

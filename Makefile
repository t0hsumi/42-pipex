NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG = # -g -fsanitize=address

SRCS = ft_pipex.c ft_split.c ft_utils.c ft_utils_libft.c ft_search_exe.c
OBJS = $(SRCS:.c=.o)

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

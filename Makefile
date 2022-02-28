NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG = # -g -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"# -fsanitize=address

SRCS = ft_pipex.c ft_split.c ft_utils.c ft_utils_libft.c ft_search_exe.c
OBJS = $(SRCS:.c=.o)

B_SRCS = ft_pipex_bonus.c ft_split_bonus.c ft_utils_bonus.c ft_utils_libft_bonus.c ft_search_exe_bonus.c ft_pipex_utils_bonus.c
B_OBJS = $(B_SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

bonus: $(B_OBJS)
	$(CC) $(B_OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

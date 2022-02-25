#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int	g_cmd_status;

enum
{
	Executable = 1,
	PermissionDenied,
	NoSuchFileOrDir
};

/* ft_utils.c */
void	error(const char *funcname);
void	free_2d_array(char **str);

/* ft_search_exe.c */
void	execute(char *argv, char **envp);

/* ft_utils_libft.c */
void	ft_putstr_fd(const char *str, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);

/* ft_pipex.c */
void	pipex(char **argv, char **envp);
void	launch_cmd1(int pipefd[2], char **argv, char **envp);
void	launch_cmd2(int pipefd[2], char **argv, char **envp);
void	parent_process(int pipefd[2], pid_t child2);

/* ft_split.c */
char	**ft_split(char const *s, char c);

#endif

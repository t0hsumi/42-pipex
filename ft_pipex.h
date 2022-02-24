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

/* ft_utils.c */
void	error(const char *funcname);
void	execute(char *argv, char **envp);

/* ft_utils_libft.c */
void	ft_putstr_fd(const char *str, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

/* ft_pipex.c */
void	pipex(int infile, int outfile, char **argv, char **envp);
void	launch_cmd1(int infile, int pipefd[2], char **argv, char **envp);
void	launch_cmd2(int outfile, int pipefd[2], char **argv, char **envp);
void	parent_process(int pipefd[2], pid_t child2);

/* ft_split.c */
char	**ft_split(char const *s, char c);

#endif

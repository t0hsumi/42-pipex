#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

void	ft_putsrt_fd(const char *str, int fd);
size_t	ft_strlen(const char *s);
void	error(const char *funcname);
void	ft_pipex(int infile, int outfile, char **argv, char **envp);
void	launch_cmd1(int infile, int pipefd[2], char **argv, char **envp);
void	launch_cmd2(int outfile, int pipefd[2], char **argv, char **envp);

#endif

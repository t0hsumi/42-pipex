#include "ft_pipex_bonus.h"

void	xpipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		error("pipe");
}

pid_t	xfork(void)
{
	pid_t	res;

	res = fork();
	if (res == -1)
		error("fork");
	return (res);
}

void	xdup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		error("dup2");
}

void	xclose(int fd)
{
	if (close(fd) == -1)
		error("close");
}

int	xopen(char *pathname, int flags, mode_t mode)
{
	int	res;

	res = open(pathname, flags, mode);
	if (res == -1)
		error("open");
	return (res);
}

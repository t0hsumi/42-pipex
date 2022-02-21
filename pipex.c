#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	pid_t	child;
	int		wstatus;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (infile < 0 || outfile < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (pipe(pipedf) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		child = fork();
		if (child < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child == 0)
		{
			child_process();
		}
		waitpid(child, &wstatus, 0);
	}
	else
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
	return (0);
}

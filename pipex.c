#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	pid_t	child1;
	pid_t	child2;
	int		wstatus;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (infile < 0 || outfile < 0)
			error("open");
		if (pipe(pipedf) == -1)
			error("pipe");
		child1 = fork();
		if (child1 < 0)
			error("fork");
		if (child1 == 0)
		{
			launch_cmd1();
		}
		child2 = fork();
		if (child2 < 0)
			error("fork");
		if (child2 == 0)
		{
			launch_cmd2();
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(child1, &wstatus, 0);
		waitpid(child2, &wstatus, 0);
	}
	else
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
	return (0);
}

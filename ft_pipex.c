#include "ft_pipex.h"
#include <fcntl.h>

/* check status of child2 process and set exit status, output error (if there is a signal) */
void	parent_process(int pipefd[2], pid_t child2)
{
	int	wstatus;

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child2, &wstatus, 0);
}

void	launch_cmd1(int infile, int pipefd[2], char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error("open");
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	execute(argv[2], envp);
}

void	launch_cmd2(int outfile, int pipefd[2], char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error("close");
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(outfile);
	execute(argv[3], envp);
}

/* maybe dont have to check status of child1 */
void	pipex(char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	child1;
	pid_t	child2;
	int		wstatus;

	if (pipe(pipefd) == -1)
		error("pipe");
	child1 = fork();
	if (child1 < 0)
		error("fork");
	if (child1 == 0)
		launch_cmd1(pipefd, argv, envp);
	child2 = fork();
	if (child2 < 0)
		error("fork");
	if (child2 == 0)
	{
		waitpid(child1, &wstatus, 0);
		launch_cmd2(pipefd, argv, envp);
	}
	parent_process(pipefd, child2);
}

int main(int argc, char **argv, char **envp)
{
	/* int		infile; */
	/* int		outfile; */

	if (argc == 5)
	{
		/* infile = open(argv[1], O_RDONLY); */
		/* outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); */
		/* if (infile < 0 || outfile < 0) */
		/* 	error("open"); */
		pipex(argv, envp);
	}
	else
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
	return (0);
}

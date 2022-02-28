#include "ft_pipex_bonus.h"

/* check status of child2 process and exit status,
 * output error (if there is a signal) */
void	parent_process(int pipefd[2], pid_t child1, pid_t child2)
{
	int	wstatus;

	if (close(pipefd[0]) < 0 || close(pipefd[1]) < 0)
		error("open");
	waitpid(child1, &wstatus, 0);
	waitpid(child2, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGSEGV)
			ft_putstr_fd("Segmentation fault: 11\n", 2);
		else if (WTERMSIG(wstatus) == SIGABRT)
			ft_putstr_fd("Abort trap: 6\n", 2);
		else if (WTERMSIG(wstatus) == SIGBUS)
			ft_putstr_fd("Bus error: 10\n", 2);
		else
			ft_putstr_fd("Unknown signal detected\n", 2);
		exit(WTERMSIG(wstatus) + 128);
	}
	if (WIFEXITED(wstatus))
		exit(WEXITSTATUS(wstatus));
}

/* infile -> cmd1 -> pipefd[1] */
void	launch_cmd1(int pipefd[2], char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error("open");
	if (dup2(pipefd[1], STDOUT_FILENO) < 0 || dup2(infile, STDIN_FILENO) < 0)
		error("dup2");
	if (close(pipefd[0]) < 0 || close(pipefd[1]) < 0 || close(infile) < 0)
		error("close");
	execute(argv[2], envp);
}

/* pipefd[0] -> cmd2 -> outfile */
void	launch_cmd2(int pipefd[2], char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error("open");
	if (dup2(pipefd[0], STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0)
		error("dup2");
	if (close(pipefd[0]) < 0 || close(pipefd[1]) < 0 || close(outfile) < 0)
		error("close");
	execute(argv[3], envp);
}

/* maybe dont have to check status of child1 */
void	pipex(char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipefd) == -1)
		error("pipe");
	child1 = fork();
	if (child1 < 0)
		error("fork");
	else if (child1 == 0)
		launch_cmd1(pipefd, argv, envp);
	else
	{
		child2 = fork();
		if (child2 < 0)
			error("fork");
		else if (child2 == 0)
			launch_cmd2(pipefd, argv, envp);
		else
			parent_process(pipefd, child1, child2);
	}
}

/* check cmdline arg and stop in case of error */
int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
		pipex(argv, envp);
	else
		usage_error();
	return (0);
}

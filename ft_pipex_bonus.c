#include "ft_pipex_bonus.h"
#include <unistd.h>

/* check status of child2 process and exit status,
 * output error (if there is a signal) */
void	parent_process(pid_t *childlen)
{
	int	wstatus;

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

pid_t	launch_cmd(char *argv, char **envp)
{
	int		pipefd[2];
	pid_t	child;

	if (pipe(pipefd) == -1)
		error("pipe");
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error("dup2")
	child = fork();
	if (child < 0)
		error("fork");
	else if (child == 0)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			error("dup2");
		if (close(pipefd[0]) < 0 || close(pipefd[1]) < 0)
			error("close");
		execute(argc, envp);
	}
	else
	{
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
			error("dup2");
		if (close(pipefd[0]) < 0 || close(pipefd[1]) < 0)
			error("close");
	}
	return (child);
}

/* check cmdline arg and stop in case of error */
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	infile;
	int	outfile;
	pid_t	master_child;
	pid_t	processes[argc - 3];

	if (argc < 5 || (!ft_strcmp(argv[1], "here_doc") && argc == 5))
		usage_error();
	else
	{
		if (ft_strcmp(argv[1], "here_doc") == 0) 
		{
			i = 3;
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (outfile < 0)
				error("open");
			here_doc(argv[2]);
		}
		else
		{
			i = 2;
			infile = open(argv[1], O_RDONLY, 0644);
			outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (infile < 0 || outfile < 0)
				error("open");
			if (dup2(infile, STDIN_FILENO) < 0)
				error("dup2");
		}
		master_child = fork();
		if (master_child < 0)
			error("fork");
		else if (master_child == 0)
		{
			while (i < argc - 2)
				launch_cmd(argv[i], envp);
		}
		else
			parent_process(processes);
	}
	return (0);
}

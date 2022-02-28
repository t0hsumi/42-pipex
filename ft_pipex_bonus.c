#include "ft_pipex_bonus.h"
#include <unistd.h>

/* check status of child2 process and exit status,
 * output error (if there is a signal) */
void	parent_process(pid_t *children)
{
	int	wstatus;
	int	i;

	i = 0;
	while (children[i])
		waitpid(children[i], &wstatus, 0);
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
		error("dup2");
	child = fork();
	if (child < 0)
		error("fork");
	else if (child == 0)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			error("dup2");
		if (close(pipefd[0]) < 0 || close(pipefd[1]) < 0)
			error("close");
		execute(argv, envp);
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

pid_t	launch_last_cmd(char *argv, char **envp, int outfile)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		error("fork");
	else if (child == 0)
	{
		if (dup2(outfile, STDOUT_FILENO) < 0)
			error("dup2");
		if (close(outfile) < 0)
			error("close");
		execute(argv, envp);
	}
	else
	{
		if (close(outfile) < 0)
			error("close");
	}
	return (child);
}

void	here_doc(char *limiter)
{
	int	pipefd[2];
	char	*line;
	pid_t	child;

	if (pipe(pipefd) < 0)
		error("pipe");
	child = fork();
	if (child < 0)
		error("fork");
	else if (child == 0)
	{
		close(pipefd[0]);
		
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			error("dup2");
		if (close(fd[0]) < 0 || close(fd[1]) < 0)
			error("close");
		waitpid(child, NULL, 0);
	}
}

/* check cmdline arg and stop in case of error */
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	j;
	int	infile;
	int	outfile;
	pid_t	master_child;
	pid_t	*processes;

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
			processes = (pid_t *)malloc(sizeof(pid_t) * (argc - 4));
			if (!processes)
				error("malloc");
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
			processes = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
			if (!processes)
				error("malloc");
		}
		j = 0;
		master_child = fork();
		if (master_child < 0)
			error("fork");
		else if (master_child == 0)
		{
			while (i < argc - 2)
				processes[j++] = launch_cmd(argv[i++], envp);
		}
		else
		{
			processes[j] = launch_last_cmd(argv[i], envp, outfile);
			parent_process(processes);
		}
	}
}

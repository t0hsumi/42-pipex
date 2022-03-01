/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:31:08 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/02 00:03:06 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

/* check status of child2 process and exit status,
 * output error (if there is a signal) */
void	parent_process(pid_t *children, int len)
{
	int	wstatus;
	int	i;

	i = 0;
	while (i <= len)
		waitpid(children[i++], &wstatus, 0);
	free(children);
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

pid_t	launch_cmd(char *argv, char **envp, int *pipe_prev)
{
	int		pipefd[2];
	pid_t	child;

	if (pipe(pipefd) == -1)
		error("pipe");
	child = fork();
	if (child < 0)
		error("fork");
	else if (child == 0)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0
			|| dup2(*pipe_prev, STDIN_FILENO) < 0)
			error("dup2");
		if (close(pipefd[0]) < 0 || close(pipefd[1]) < 0)
			error("close");
		execute(argv, envp);
	}
	else
	{
		if (close(pipefd[1]) < 0
			|| (*pipe_prev != STDIN_FILENO && close(*pipe_prev) < 0))
			error("close");
		*pipe_prev = pipefd[0];
	}
	return (child);
}

pid_t	launch_last_cmd(char *argv, char **envp, int outfile, int *pipe_prev)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		error("fork");
	else if (child == 0)
	{
		if (dup2(outfile, STDOUT_FILENO) < 0
			|| dup2(*pipe_prev, STDIN_FILENO) < 0)
			error("dup2");
		if (close(outfile) < 0
			|| (*pipe_prev != STDIN_FILENO && close(*pipe_prev) < 0))
			error("close");
		execute(argv, envp);
	}
	else
	{
		if (close(outfile) < 0
			|| (*pipe_prev != STDIN_FILENO && close(*pipe_prev) < 0))
			error("close");
	}
	return (child);
}

void	here_doc(char *limiter)
{
	int		pipefd[2];
	char	*line;
	pid_t	child;

	xpipe(pipefd);
	child = xfork();
	if (child == 0)
	{
		xclose(pipefd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(pipefd[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		xdup2(pipefd[0], STDIN_FILENO);
		xclose(pipefd[0]);
		xclose(pipefd[1]);
		waitpid(child, NULL, 0);
	}
}

/* check cmdline arg and stop in case of error */
int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	int		infile;
	int		outfile;
	pid_t	*processes;
	int		pipe_prev;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc == 5))
		usage_error();
	else
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		{
			i = 2;
			outfile = xopen(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			processes = (pid_t *)malloc(sizeof(pid_t) * (argc - 4));
			if (!processes)
				error("malloc");
			here_doc(argv[2]);
		}
		else
		{
			i = 1;
			infile = xopen(argv[1], O_RDONLY, 0644);
			outfile = xopen(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			xdup2(infile, STDIN_FILENO);
			processes = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
			if (!processes)
				error("malloc");
		}
		j = -1;
		pipe_prev = STDIN_FILENO;
		while (++i < argc - 2)
			processes[++j] = launch_cmd(argv[i], envp, &pipe_prev);
		processes[++j] = launch_last_cmd(argv[argc - 2], envp, outfile, &pipe_prev);
		parent_process(processes, j);
	}
}

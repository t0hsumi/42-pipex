/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_check_cmd_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:52:25 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/13 17:04:51 by tohsumi          ###   ########.fr       */
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

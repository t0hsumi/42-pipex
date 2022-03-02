/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:31:08 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/02 13:52:25 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

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

void	pipex(int argc, char **argv, char **envp)
{
	int		i;
	int		j;
	int		infile;
	int		outfile;
	pid_t	*processes;
	int		pipe_prev;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		i = 2;
		outfile = xopen(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		processes = (pid_t *)xmalloc(sizeof(pid_t) * (argc - 4));
		here_doc(argv[2]);
	}
	else
	{
		i = 1;
		infile = xopen(argv[1], O_RDONLY, 0644);
		outfile = xopen(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		xdup2(infile, STDIN_FILENO);
		// xclose(infile);
		processes = (pid_t *)xmalloc(sizeof(pid_t) * (argc - 3));
	}
	j = -1;
	pipe_prev = STDIN_FILENO;
	while (++i < argc - 2)
		processes[++j] = launch_cmd(argv[i], envp, &pipe_prev);
	processes[++j] = launch_last_cmd(argv[argc - 2], envp, outfile, &pipe_prev);
	parent_process(processes, j);
}

/* check cmdline arg and stop in case of error */
int	main(int argc, char **argv, char **envp)
{
	if (argc < 5
		|| (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc == 5))
		usage_error();
	else
		pipex(argc, argv, envp);
}

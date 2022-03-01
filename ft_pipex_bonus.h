/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:29:42 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/02 00:14:13 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_BONUS_H
# define FT_PIPEX_BONUS_H

# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "get_next_line_bonus.h"

int	g_cmd_status;

enum
{
	CommandNotFound,
	Executable = 1,
	PermissionDenied,
};

/* ft_utils_bonus.c */
void	free_2d_array(char **str);
void	free_err(const char *funcname, char **str);
void	error(const char *funcname);
int		check_cmd_status(char *path);
void	usage_error(void);

/* ft_search_exe_bonus.c */
void	execute(char *argv, char **envp);

/* ft_utils_libft_bonus.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(const char *str, int fd);
char	*ft_strdup(const char *s1);

/* ft_split_bonus.c */
char	**ft_split(char const *s, char c);

/* ft_exit_bonus.c */
void	xpipe(int pipefd[2]);
pid_t	xfork(void);
void	xdup2(int oldfd, int newfd);
void	xclose(int fd);
int		xopen(char *pathname, int flags, mode_t mode);

/* ft_launch_check_cmd_bonus.c */
void	parent_process(pid_t *childlen, int len);
pid_t	launch_cmd(char *argv, char **envp, int *pipe_prev);
pid_t	launch_last_cmd(char *argv, char **envp, int outfile, int *pipe_prev);

#endif

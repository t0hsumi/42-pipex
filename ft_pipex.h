/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:29:42 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/13 17:05:11 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

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

enum
{
	CommandNotFound,
	Executable = 1,
	PermissionDenied,
};

/* ft_utils.c */
void	free_2d_array(char **str);
void	free_err(const char *funcname, char **str);
void	error(const char *funcname);
int		check_cmd_status(char *path);

/* ft_search_exe.c */
void	execute(char *argv, char **envp);

/* ft_utils_libft.c */
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(const char *str, int fd);
char	*ft_strdup(const char *s1);

/* ft_pipex.c */
void	parent_process(int pipefd[2], pid_t child1, pid_t child2);
void	launch_cmd1(int pipefd[2], char **argv, char **envp);
void	launch_cmd2(int pipefd[2], char **argv, char **envp);
void	pipex(char **argv, char **envp);

/* ft_split.c */
char	**ft_split(char const *s, char c);

/* ft_strchr.c */
char	*ft_strchr(const char *s, int chr);

#endif

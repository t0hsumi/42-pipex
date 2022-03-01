/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:29:41 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/01 23:31:09 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

void	free_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_err(const char *funcname, char **str)
{
	free_2d_array(str);
	error(funcname);
}

void	error(const char *funcname)
{
	perror(funcname);
	exit(EXIT_FAILURE);
}

int	check_cmd_status(char *path)
{
	if (access(path, X_OK) == 0)
		return (Executable);
	else if (access(path, F_OK) == 0)
		return (PermissionDenied);
	return (CommandNotFound);
}

void	usage_error(void)
{
	ft_putstr_fd("Error: Bad argument\n", 2);
	ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
	ft_putstr_fd("    ./pipex here_doc LIMITER cmd1 ... cmdn file2\n", 2);
	exit(EXIT_FAILURE);
}

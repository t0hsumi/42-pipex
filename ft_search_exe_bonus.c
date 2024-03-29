/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_exe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:29:41 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/13 17:04:56 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static char	*make_cmd_path(char **env, int check_index, char **cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(env[check_index], "/");
	res = ft_strjoin(tmp, cmd[0]);
	if (!res || !tmp)
	{
		free(res);
		free(tmp);
		free_2d_array(env);
		free_2d_array(cmd);
		error("malloc");
	}
	free(tmp);
	return (res);
}

static int	is_path(char **env_path, int index, char **cmd, char **path)
{
	int	cmd_status;

	*path = make_cmd_path(env_path, index, cmd);
	cmd_status = check_cmd_status(*path);
	if (cmd_status == Executable)
		free_2d_array(env_path);
	return (cmd_status);
}

static int	is_full_path_cmd(char **cmd, char **path, int *cmd_status)
{
	*cmd_status = check_cmd_status(cmd[0]);
	if (*cmd_status == Executable)
	{
		*path = ft_strdup(cmd[0]);
		if (!*path)
			free_err("malloc", cmd);
		return (1);
	}
	return (0);
}

static char	*search_path(char **cmd, char **envp, int *cmd_status)
{
	int		i;
	char	**env_path;
	char	*path;

	i = 0;
	if (ft_strchr(cmd[0], '/'))
		if (is_full_path_cmd(cmd, &path, cmd_status))
			return (path);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	env_path = ft_split(envp[i] + 5, ':');
	if (!env_path)
		free_err("malloc", cmd);
	i = -1;
	while (env_path[++i])
	{
		*cmd_status = is_path(env_path, i, cmd, &path);
		if (*cmd_status == Executable)
			return (path);
		free(path);
	}
	free_2d_array(env_path);
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		cmd_status;

	cmd_status = CommandNotFound;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		error("malloc");
	path = search_path(cmd, envp, &cmd_status);
	if (cmd_status == PermissionDenied)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_2d_array(cmd);
		exit(126);
	}
	else if (cmd_status == CommandNotFound)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_2d_array(cmd);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
		error("execve");
}

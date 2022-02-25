#include "ft_pipex.h"

static void	free_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

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

static int	check_cmd_status(char *path)
{
	if (access(path, X_OK) == 0)
		return (Executable);
	else if (access(path, F_OK) == 0)
		return (PermissionDenied);
	return (NoSuchFileOrDir);
}

static char	*search_path(char **cmd, char **envp)
{
	int		i;
	int		cmd_status;
	char	**env_path;
	char	*path;

	i = 0;
	g_cmd_status = check_cmd_status(cmd[0]);
	if (g_cmd_status == Executable)
	{
		path = ft_strdup(cmd[0]);
		if (!path)
			error("malloc");
		return (path);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	env_path = ft_split(envp[i] + 5, ':');
	if (!env_path)
	{
		free_2d_array(cmd);
		error("malloc");
	}
	i = 0;
	while (env_path[i])
	{
		path = make_cmd_path(env_path, i, cmd);
		cmd_status = check_cmd_status(path);
		if (cmd_status == Executable)
		{
			g_cmd_status = cmd_status;
			free_2d_array(env_path);
			return (path);
		}
		else if (cmd_status == PermissionDenied)
			g_cmd_status = PermissionDenied;
		free(path);
		i++;
	}
	free_2d_array(env_path);
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error("malloc");
	path = search_path(cmd, envp);
	if (g_cmd_status == PermissionDenied)
	{
		free_2d_array(cmd);
		ft_putstr_fd("command : Permission denied\n", 2);
		exit(126);
	}
	else if (g_cmd_status == NoSuchFileOrDir)
	{
		free_2d_array(cmd);
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
		error("execve");
}

void	error(const char *funcname)
{
	perror(funcname);
	exit(EXIT_FAILURE);
}

#include "ft_pipex.h"

static char	*make_cmd_path(char *env, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(env, "/");
	if (!tmp)
		error("malloc");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!res)
		error("malloc");
	return (res);
}

static char	*search_path(char *cmd, char **envp)
{
	int		i;
	char	**env_path;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	env_path = ft_split(envp[i] + 5, ':');
	if (!env_path)
		error("malloc");
	i = 0;
	while (env_path[i])
	{
		path = make_cmd_path(env_path[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (env_path[i])
		free(env_path[i++]);
	free(env_path);
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error("malloc");
	path = search_path(cmd[0], envp);
	if (!path)
	{
		i = 0;
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		error("access");
	}
	if (execve(path, cmd, envp) == -1)
		error("execve");
}

void	error(const char *funcname)
{
	perror(funcname);
	exit(EXIT_FAILURE);
}

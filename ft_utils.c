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

static char	*search_path(char **cmd, char **envp)
{
	int		i;
	char	**env_path;
	char	*path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	/* if (envp[i] == NULL) */
	/* 	no_path_case(cmd, envp); */
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
		if (access(path, X_OK) == 0)
		{
			free_2d_array(env_path);
			return (path);
		}
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
	if (!path)
	{
		free_2d_array(cmd);
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

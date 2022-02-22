#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		if (i + 1 < n)
			i++;
		else
			break ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*make_cmd_path(char *env, char *cmd)
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

char	*search_path(char *cmd, char **envp)
{
	int		i;
	char	**env_path;
	char	*path;

	i = 0;
	while(ft_strncmp(envp[i], "PATH=", 5) != 0)
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

	cmd = ft_splie(argv, ' ');
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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

void	error(const char *funcname)
{
	perror(funcname);
	exit(EXIT_FAILURE);
}


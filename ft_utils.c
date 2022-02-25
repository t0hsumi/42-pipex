#include "ft_pipex.h"

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

#include "ft_pipex.h"

void	free_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	error(const char *funcname)
{
	perror(funcname);
	exit(EXIT_FAILURE);
}

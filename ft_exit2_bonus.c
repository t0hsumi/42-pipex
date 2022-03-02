#include "ft_pipex_bonus.h"

void	*xmalloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		error("malloc");
	return (res);
}

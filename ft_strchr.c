#include "ft_pipex.h"

char	*ft_strchr(const char *s, int chr)
{
	char	c;
	int		i;

	c = (char)chr;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

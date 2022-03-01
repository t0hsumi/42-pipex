/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:29:41 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/01 23:31:09 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static char	*ft_strndp(const char *s1, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(ptr + i) = *(char *)(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

static void	*freemem(char **dptr, int k)
{
	while (k >= 0)
		free(dptr[k--]);
	free(dptr);
	return (NULL);
}

static char	**ft_allocate(char const *s, char c, char **dptr)
{
	size_t	posi;
	size_t	len;
	size_t	i;

	posi = 0;
	i = 0;
	while (s[posi])
	{
		while (s[posi] == c)
			posi++;
		if (s[posi] && s[posi] != c)
		{
			len = 0;
			while (s[posi] != c && s[posi])
			{
				len++;
				posi++;
			}
			dptr[i] = ft_strndp(s + posi - len, len);
			if (!dptr[i++])
				return (freemem(dptr, --i));
		}
	}
	dptr[i] = NULL;
	return (dptr);
}

char	**ft_split(char const *s, char c)
{
	char	**dptr;
	size_t	words;
	size_t	i;

	i = 0;
	words = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	dptr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dptr)
		return (NULL);
	return (ft_allocate(s, c, dptr));
}

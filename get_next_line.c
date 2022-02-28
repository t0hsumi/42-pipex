/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:46:34 by tohsumi           #+#    #+#             */
/*   Updated: 2021/11/19 11:58:45 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line(char **line, char **memo)
{
	char	*box;
	int		i;
	int		j;

	i = ft_new_line_pos(*memo, '\n');
	j = -1;
	*line = ft_strndup(*memo, i);
	if (!*line)
		return (my_free(memo, NULL, NULL, NULL));
	box = (char *)malloc(sizeof(char) * (ft_strlen(memo[0]) - i));
	if (!box)
		return (my_free(memo, line, NULL, NULL));
	while (memo[0][i + 1 + ++j])
		box[j] = memo[0][i + 1 + j];
	box[j] = '\0';
	my_free(memo, NULL, NULL, NULL);
	*memo = ft_strndup(box, ft_strlen(box));
	my_free(&box, NULL, NULL, NULL);
	if (!*memo)
		return (my_free(line, NULL, NULL, NULL));
	return (NEW_LINE);
}

int	new_line_in_tmp(char **line, char **memo, char *tmp, int pos)
{
	char	*box;
	int		i;
	int		j;

	i = -1;
	j = -1;
	*line = (char *)malloc(sizeof(char) * (ft_strlen(*memo) + pos + 1));
	box = (char *)malloc(sizeof(char) * (ft_strlen(tmp) - pos));
	if (!*line || !box)
		return (my_free(line, memo, &tmp, &box));
	while (memo[0][++i])
		line[0][i] = memo[0][i];
	while (tmp[++j] != '\n')
		line[0][i + j] = tmp[j];
	line[0][ft_strlen(*memo) + pos] = '\0';
	i = -1;
	while (tmp[pos + 1 + ++i])
		box[i] = tmp[pos + 1 + i];
	box[i] = '\0';
	my_free(memo, NULL, NULL, NULL);
	*memo = ft_strndup(box, ft_strlen(box));
	if (!*memo)
		return (my_free(&box, &tmp, line, NULL));
	my_free(&box, &tmp, NULL, NULL);
	return (NEW_LINE);
}

int	no_new_line(char **line, char **memo, char *tmp, ssize_t n)
{
	char	*box;
	int		pos;

	pos = ft_new_line_pos(tmp, '\n');
	if (pos >= 0)
		return (new_line_in_tmp(line, memo, tmp, pos));
	box = ft_strndup(*memo, ft_strlen(*memo));
	if (!box)
		return (my_free(memo, &tmp, NULL, NULL));
	my_free(memo, NULL, NULL, NULL);
	*memo = ft_strjoin(box, tmp);
	my_free(&box, &tmp, NULL, NULL);
	if (!*memo)
		return (ERROR);
	if (n < (ssize_t)BUFFER_SIZE)
	{
		*line = ft_strndup(*memo, ft_strlen(*memo));
		if (!line)
			return (my_free(memo, NULL, NULL, NULL));
		my_free(memo, NULL, NULL, NULL);
		return (END_OF_FILE);
	}
	return (NOT_UNTIL);
}

int	get_next_line_prev(int fd, char **line)
{
	ssize_t			n;
	int				flag;
	static char		*memo;
	char			*tmp;
	const size_t	bs = (size_t)BUFFER_SIZE;

	flag = 2;
	if (!memo)
		memo = ft_strndup("", ft_strlen(""));
	if (!memo || !line || fd < 0 || bs <= 0 || bs > SSIZE_MAX)
		return (my_free(&memo, NULL, NULL, NULL));
	while (flag == 2)
	{
		if (ft_new_line_pos(memo, '\n') != -1)
			return (new_line(line, &memo));
		tmp = (char *)malloc(sizeof(char) * (bs + 1));
		n = read(fd, tmp, bs);
		if (n == -1)
			return (my_free(&tmp, &memo, NULL, NULL));
		tmp[n] = 0;
		flag = no_new_line(line, &memo, tmp, n);
	}
	return (flag);
}

char	*get_next_line(int fd)
{
	char	*tmp;
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line_prev(fd, &tmp);
	if (ret > 0)
	{
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		return (line);
	}
	else if (ret == 0)
	{
		if (tmp[0] == '\0')
		{
			free(tmp);
			tmp = NULL;
			return (NULL);
		}
		return (tmp);
	}
	else
		return (NULL);
}

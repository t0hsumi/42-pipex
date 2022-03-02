/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohsumi <tohsumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:52:24 by tohsumi           #+#    #+#             */
/*   Updated: 2022/03/02 13:52:24 by tohsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

void	*xmalloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		error("malloc");
	return (res);
}

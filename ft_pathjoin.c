/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 09:35:01 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/29 10:37:47 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_pathjoin(char *path, char *exec)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(path);
	len2 = ft_strlen(exec);
	i = -1;
	j = -1;
	res = malloc(len1 + len2 + 2);
	if (!res)
		return (NULL);
	while (++i < len1)
		res[i] = path[i];
	res[i++] = '/';
	while (++j < len2)
		res[i + j] = exec[j];
	res[i + j] = '\0';
	return (res);
}

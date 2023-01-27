/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:12:33 by aberneli          #+#    #+#             */
/*   Updated: 2021/12/14 10:43:33 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*err_strjoin(const char *head, const char *str)
{
	char	*res;
	size_t	a;
	size_t	b;
	size_t	i;
	size_t	j;

	a = ft_strlen(head);
	b = ft_strlen(str);
	res = malloc(a + b + 2);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < a)
		res[i] = head[i];
	j = -1;
	while (++j < b)
		res[i + j] = str[j];
	res[i + j] = '\n';
	res[i + j + 1] = '\0';
	return (res);
}

int	err_denied(const char *name)
{
	char	*head;
	char	*total;

	head = "pipex: permission denied: ";
	total = err_strjoin(head, name);
	if (!total)
		write(2, "pipex: failed to report error\n", 30);
	else
		write(2, total, ft_strlen(total));
	free(total);
	return (1);
}

int	err_notfound(const char *name)
{
	char	*head;
	char	*total;

	head = "pipex: command not found: ";
	total = err_strjoin(head, name);
	if (!total)
		write(2, "pipex: failed to report error\n", 30);
	else
		write(2, total, ft_strlen(total));
	free(total);
	return (1);
}

int	err_report(void)
{
	char	*str;
	char	*name;
	char	*total;

	str = strerror(errno);
	name = "pipex: ";
	total = err_strjoin(name, str);
	if (!total)
		write(2, "pipex: failed to report error\n", 30);
	else
		write(2, total, ft_strlen(total));
	free(total);
	return (1);
}

int	err_put(const char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

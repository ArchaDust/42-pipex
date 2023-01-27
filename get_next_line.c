/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:49:49 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/05 08:49:54 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl	*gnl_find_fd(t_gnl **gnl, int fd)
{
	t_gnl	*res;

	res = *gnl;
	while (res)
	{
		if (fd == res->fd)
			return (res);
		res = res->next;
	}
	res = malloc(sizeof(t_gnl));
	if (!res)
		return (NULL);
	res->fd = fd;
	res->save = NULL;
	res->next = *gnl;
	*gnl = res;
	return (res);
}

static void	gnl_eject(t_gnl **gnl, t_gnl *curr)
{
	t_gnl	*tmp;

	if (!curr)
		return ;
	if (*gnl == curr)
		*gnl = curr->next;
	else
	{
		tmp = *gnl;
		while (tmp->next != curr)
			tmp = tmp->next;
		tmp->next = curr->next;
	}
	free(curr->save);
	free(curr);
}

static int	gnl_read(t_gnl *curr)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		rd;

	rd = read(curr->fd, buf, BUFFER_SIZE);
	buf[rd] = '\0';
	if (rd < 1)
		return (0);
	tmp = gnl_strcatre(curr->save, buf);
	if (curr->save)
		free(curr->save);
	curr->save = tmp;
	while (!gnl_strchr(curr->save, '\n'))
	{
		rd = read(curr->fd, buf, BUFFER_SIZE);
		buf[rd] = '\0';
		if (rd < 1)
			return (1);
		tmp = gnl_strcatre(curr->save, buf);
		free(curr->save);
		curr->save = tmp;
	}
	return (2);
}

static char	*gnl_extract(t_gnl **gnl, t_gnl *curr)
{
	char	*res;
	char	*pos;
	char	*tmp;
	size_t	len;

	pos = gnl_strchr(curr->save, '\n');
	if (!pos)
	{
		tmp = NULL;
		if (curr->save[0] != '\0')
			tmp = gnl_substr(curr->save, 0, gnl_strlen(curr->save));
		gnl_eject(gnl, curr);
		return (tmp);
	}
	len = (size_t)(pos - curr->save);
	res = gnl_substr(curr->save, 0, len + 1);
	tmp = gnl_substr(curr->save, len + 1, gnl_strlen(curr->save) - (len + 1));
	free(curr->save);
	curr->save = tmp;
	return (res);
}

char	*get_next_line(int fd)
{
	static t_gnl	*gnl = NULL;
	t_gnl			*curr;
	char			*tmp;
	int				err;

	curr = gnl_find_fd(&gnl, fd);
	if (!curr)
		return (NULL);
	err = 2;
	if (!gnl_strchr(curr->save, '\n'))
		err = gnl_read(curr);
	if (err < 1 && curr->save)
	{
		tmp = NULL;
		if (curr->save[0] != '\0')
			tmp = gnl_substr(curr->save, 0, gnl_strlen(curr->save));
		gnl_eject(&gnl, curr);
		return (tmp);
	}
	if (err < 1 && !curr->save)
	{
		gnl_eject(&gnl, curr);
		return (NULL);
	}
	return (gnl_extract(&gnl, curr));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:44:39 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/04 20:00:39 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	if (!s)
		return (NULL);
	if (c == '\0')
		return (ptr + gnl_strlen(ptr));
	while (ptr[i] != '\0')
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}

size_t	gnl_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	if (size < 1)
		return (gnl_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	if (src[i] == '\0')
		return (gnl_strlen(src));
	if (i < size)
		return (gnl_strlen(src));
	return (i);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
	if (start >= slen)
		slen = 0;
	else if (slen < start + len)
		slen = slen - start;
	else
		slen = len;
	res = malloc(slen + 1);
	if (!res)
		return (NULL);
	gnl_strlcpy(res, &s[start], slen + 1);
	return (res);
}

char	*gnl_strcatre(char *str, char *cat)
{
	char	*re;
	size_t	s1;
	size_t	s2;

	s1 = gnl_strlen(str);
	s2 = gnl_strlen(cat);
	re = malloc(s1 + s2 + 1);
	if (!re)
		return (NULL);
	gnl_strlcpy(re, str, s1 + 1);
	gnl_strlcpy(&re[s1], cat, s2 + 1);
	return (re);
}

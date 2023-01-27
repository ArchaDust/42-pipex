/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:28:07 by aberneli          #+#    #+#             */
/*   Updated: 2021/11/04 19:59:14 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_gnl
{
	struct s_gnl	*next;
	int				fd;
	char			*save;
}					t_gnl;

// get_next_line.c
char	*get_next_line(int fd);

//get_next_line_utils.c
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_strlcpy(char *dest, const char *src, size_t size);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strcatre(char *str, char *cat);

#endif

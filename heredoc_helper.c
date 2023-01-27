/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:06:14 by aberneli          #+#    #+#             */
/*   Updated: 2021/12/14 14:59:38 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_cmpnl(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (*s2 == '\0')
	{
		if (*s1 == '\n')
			if (*(s1 + 1) == '\0')
				return (0);
		return (1);
	}
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static void	heredoc_read(t_pipex *p)
{
	char	*line;

	line = get_next_line(0);
	if (!line)
		exit(err_report());
	while (line)
	{
		if (ft_cmpnl(line, p->limiter) == 0)
			break ;
		write(1, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(1);
}

int	heredoc_helper(t_pipex *p)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		exit(err_report());
	pid = fork();
	if (pid < 0)
		exit(err_report());
	if (pid != 0)
	{
		if (close(fd[0]) < 0)
			exit(err_report());
		if (dup2(fd[1], 1) < 0)
			exit(err_report());
		if (close(fd[1]) < 0)
			exit(err_report());
		heredoc_read(p);
		return (-2);
	}
	if (close(fd[1]))
		exit(err_report());
	return (fd[0]);
}

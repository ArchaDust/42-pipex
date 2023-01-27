/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:54:19 by aberneli          #+#    #+#             */
/*   Updated: 2021/12/14 15:31:06 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	sub_process(t_pipex *p, int pipe[2], int prev[2], int argc)
{
	if (dup2(prev[1], 1) < 0)
		exit(err_report());
	if (dup2(pipe[0], 0) < 0)
		exit(err_report());
	if (close(pipe[0]) < 0)
		exit(err_report());
	if (close(pipe[1]) < 0)
		exit(err_report());
	if (close(prev[0]) < 0)
		exit(err_report());
	if (close(prev[1]) < 0)
		exit(err_report());
	exec_helper(p, argc);
}

static int	out_process(t_pipex *p, int prev[2], int argc)
{
	int	out;

	if (!p->heredoc)
		out = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		out = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (out < 0)
		exit(1);
	if (dup2(out, 1) < 0)
		exit(err_report());
	if (dup2(prev[0], 0) < 0)
		exit(err_report());
	if (close(prev[0]) < 0)
		exit(err_report());
	if (close(prev[1]) < 0)
		exit(err_report());
	if (close(out) < 0)
		exit(err_report());
	exec_helper(p, argc);
	return (-1);
}

static int	in_process(t_pipex *p, int pipe[2], int argc)
{
	int	in;

	if (p->heredoc)
		in = heredoc_helper(p);
	else
		in = open(p->argv[1], 0);
	if (in == -2)
		return (1 + close(pipe[0]) + close(pipe[1]));
	if (in < 0)
		exit(err_report());
	if (dup2(pipe[1], 1) < 0)
		exit(err_report());
	if (dup2(in, 0) < 0)
		exit(err_report());
	if (close(pipe[0]) < 0)
		exit(err_report());
	if (close(pipe[1]) < 0)
		exit(err_report());
	if (close(in) < 0)
		exit(err_report());
	exec_helper(p, argc);
	return (-1);
}

static int	pipeline(t_pipex *p, int *prev, int argc)
{
	int		pfd[2];
	int		pid;

	if (argc == 2 + p->heredoc)
		return (in_process(p, prev, argc));
	if (pipe(pfd) < 0)
		exit(err_report());
	pid = fork();
	if (pid < 0)
		exit(err_report());
	if (pid != 0)
	{
		if (prev && close(prev[0]) < 0)
			exit(err_report());
		if (prev && close(prev[1]) < 0)
			exit(err_report());
		return (pipeline(p, pfd, argc - 1));
	}
	if (argc != p->argc - 2)
		sub_process(p, pfd, prev, argc);
	if (prev && close(prev[0]) < 0)
		exit(err_report());
	if (prev && close(prev[1]) < 0)
		exit(err_report());
	return (out_process(p, pfd, argc));
}

int	pipeline_entry(t_pipex *p)
{
	int		stat;

	pipeline(p, NULL, p->argc - 2);
	if (access(p->argv[p->argc - 1], W_OK) < 0)
		err_denied(p->argv[p->argc - 1]);
	while (wait(&stat) >= 0)
	{
		if ((WIFEXITED(stat) && WEXITSTATUS(stat)) != 0 || WIFSIGNALED(stat))
		{
			if (!p->heredoc && p->unlinkstatus == 0)
				p->unlinkstatus = 1;
		}
	}
	return (1);
}

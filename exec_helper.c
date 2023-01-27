/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:46:16 by aberneli          #+#    #+#             */
/*   Updated: 2021/12/06 11:52:11 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_helper(t_pipex *p, int argc)
{
	char	**exec_arg;
	char	*exe;

	exec_arg = ft_split(p->argv[argc], ' ');
	if (!exec_arg)
		exit(err_put("pipex: alloc error\n"));
	exe = resolve_exec(exec_arg[0], p->path_var);
	if (!exe)
	{
		err_notfound(exec_arg[0]);
		ft_splclean(exec_arg);
		exit(1);
	}
	free(exec_arg[0]);
	exec_arg[0] = exe;
	if (execve(exe, exec_arg, p->envp) < 0)
	{
		ft_splclean(exec_arg);
		exit(err_report());
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:45:50 by aberneli          #+#    #+#             */
/*   Updated: 2021/12/14 14:53:39 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

static char	*find_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc < 5)
		return (err_put("pipex: not enough arguments\n"));
	p.heredoc = (ft_memcmp(argv[1], "here_doc", 9) == 0);
	p.limiter = NULL;
	if (p.heredoc)
		p.limiter = argv[2];
	if (p.heredoc && argc < 6)
		return (err_put("pipex: not enough arguments\n"));
	p.envp = envp;
	p.argc = argc;
	p.argv = argv;
	p.unlinkstatus = 0;
	if (access(argv[argc - 1], W_OK) < 0)
		p.unlinkstatus = -1;
	p.path_var = find_env_path(envp);
	if (!p.path_var)
		return (err_put("pipex: PATH not found\n"));
	pipeline_entry(&p);
	if (p.unlinkstatus == 1)
		unlink(argv[argc - 1]);
	return (0);
}

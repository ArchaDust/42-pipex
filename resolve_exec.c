/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 09:14:18 by aberneli          #+#    #+#             */
/*   Updated: 2021/12/02 13:20:47 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*resolve_exec(char *exec, char *path)
{
	char	*result;
	char	**spl_path;
	int		i;
	int		access_r;

	spl_path = ft_split(path, ':');
	if (!spl_path)
		return (NULL);
	i = 0;
	while (spl_path[i])
	{
		result = ft_pathjoin(spl_path[i], exec);
		if (result)
		{
			access_r = access(result, F_OK | X_OK);
			if (access_r == 0)
				break ;
		}
		free(result);
		result = NULL;
		i++;
	}
	ft_splclean(spl_path);
	return (result);
}

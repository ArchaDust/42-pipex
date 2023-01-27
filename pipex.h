/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:52:42 by aberneli          #+#    #+#             */
/*   Updated: 2021/12/14 16:00:37 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# include <get_next_line.h>

typedef struct s_pipex
{
	char		**envp;
	char		**argv;
	char		*path_var;
	char		*limiter;
	int			hd_fd[2];
	int			argc;
	int			heredoc;
	int			unlinkstatus;
}				t_pipex;

// ft_strlen.c
size_t	ft_strlen(const char *s);

// ft_split.c
char	**ft_split(char const *str, char c);

// ft_splclean.c
void	ft_splclean(char **spl);

// ft_pathjoin.c
char	*ft_pathjoin(char *s1, char *s2);

// resolve_exec.c -- will return a malloc'ed string
char	*resolve_exec(char *exec, char *path);

// exec_helper.c
void	exec_helper(t_pipex *p, int argc);

// err.c
int		err_denied(const char *name);
int		err_notfound(const char *name);
int		err_report(void);
int		err_put(const char *str);

// pipeline.c
int		pipeline_entry(t_pipex *p);

// heredoc_helper.c
int		heredoc_helper(t_pipex *p);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:18:44 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/29 11:23:02 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>

/*  UTILS*/

int		ft_strlen(char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	ft_freetab(char **tab);

char	*ft_strjoin(char *s1, char *s2);

void	ft_file_not_found(char *file);

/* PIPEX UTILS */

char	**ft_removepathprefix(char **paths);

char	**ft_getpaths(char **envp);

char	*ft_findcmdpath(char *cmd, char **envp, char *tmp, char *cmd_path);

int		ft_closepipe(int *pipefd);

void	ft_exec_abs(char **command, char **envp);

int		ft_is_absolute(char *cmd);

/* PUT FUNCTIONS */

void	ft_putchar(char c);

void	ft_putstr(char *s);

void	ft_putstr_fd(char *s, int fd);

void	ft_putnbr(int nb);

/* SPLIT */

int		ft_wordcount(char *s, char c);

int		ft_getwordlen(char *s, char c, int i);

void	ft_freemalloc(char **strs, int a);

char	**ft_split(char const *s, char c);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

void	ft_freesplit(char **strs);

#endif

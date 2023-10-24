/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:39:15 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/24 23:34:33 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	pipefd[2];
	int isheredoc;
} t_fd;

/*  UTILS*/

int		ft_strlen(char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	ft_freetab(char **tab);

char	*ft_strjoin(char *s1, char *s2);

/* PIPEX UTILS */

char	**ft_removepathprefix(char **paths);

char	**ft_getpaths(char **envp);

char	*ft_findcmdpath(char *cmd, char **envp);

int		ft_open_file(t_fd *fd, char *file, int b);

int		ft_closepipe(int *pipefd);

int		ft_checkargs(int argc, char **argv, char **envp);

int		ft_close(t_fd *fd);

// void	ft_exit(int e);

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

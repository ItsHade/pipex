/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:12 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/24 23:18:00 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

char	*get_next_line(int fd);

char	*ft_strjoin(char *s1, char *s2);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t elementCount, size_t elementSize);

int		ft_strlen(char *s);

void	ft_putstr_fd(char *s, int fd);

char	*ft_getnonnull(char *s1);

/* PUT FUNCTIONS */

void	ft_putchar(char c);

void	ft_putstr(char *s);

void	ft_putstr_fd(char *s, int fd);

void	ft_putnbr(int nb);

#endif

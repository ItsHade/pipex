/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:43 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/22 15:33:48 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	if (c == 0)
	{
		i = ft_strlen((char *)s);
		return (&s[i]);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

int	ft_open_file(char *file, int b)
{
	int	fd;

	if (b == 0)
		fd = open(file, O_RDONLY, 00644);
	if (b == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (b == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 00644);
	if (fd == -1)
	{
		ft_putstr("No such file or directory!: ");
		ft_putstr(file);
		ft_putchar('\n');
		exit(0);
	}
	return (fd);
}

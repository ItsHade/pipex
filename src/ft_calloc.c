/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:50:50 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/29 11:15:42 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t		mem;
	void		*ptr;

	mem = size * nmemb;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (mem / size != nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, mem);
	return (ptr);
}

int	ft_is_absolute(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	return (-1);
}

void	ft_file_not_found(char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

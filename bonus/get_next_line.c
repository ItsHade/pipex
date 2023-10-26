/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:46:27 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/26 17:27:20 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		a;
	char	*str;

	a = 0;
	i = -1;
	if (!s1)
		s1 = ft_getnonnull(s1);
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[a] != '\0')
	{
		str[i + a] = s2[a];
		a++;
	}
	str[i + a] = '\0';
	free(s1);
	return (str);
}

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

char	*get_next_line(int fd)
{
	char		*buffer;
	int			nb_bytes;
	char		*stash;
	int			buffer_size;

	buffer_size = 1;
	stash = NULL;
	ft_putstr_fd("heredoc> ", 1);
	if (fd < 0)
		return (NULL);
	nb_bytes = 1;
	buffer = ft_calloc(sizeof(char), (buffer_size + 1));
	if (!buffer)
		return (NULL);
	while (!(ft_strchr(stash, '\n')) && nb_bytes != 0)
	{
		nb_bytes = read(fd, buffer, buffer_size);
		if (nb_bytes == -1)
			return (free(buffer), NULL);
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free(buffer);
	return (stash);
}

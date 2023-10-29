/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:37:12 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/28 18:21:30 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0 || !s1)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

void	ft_freetab(char **tab)
{
	int	a;

	a = 0;
	while (tab[a] != NULL)
	{
		free(tab[a]);
		a++;
	}
	free(tab[a]);
	free(tab);
}

char	*ft_getnonnull(char *s1)
{
	s1 = malloc(sizeof(char) * 1);
	if (!s1)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		a;
	char	*str;

	a = 0;
	i = 0;
	if (!s1)
		s1 = ft_getnonnull(s1);
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[a] != '\0')
	{
		str[i + a] = s2[a];
		a++;
	}
	str[i + a] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:15:19 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/06 20:09:39 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	unsigned int	num;

	if (nb < 0)
	{
		num = -nb;
		ft_putchar('-');
	}
	else
		num = nb;
	if (num <= 9)
		ft_putchar(num + 48);
	else
	{
		ft_putnbr(num / 10);
		ft_putchar(num % 10 + 48);
	}
}

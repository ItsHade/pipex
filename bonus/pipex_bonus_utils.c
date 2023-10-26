/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:43 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/26 17:54:37 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"
#include "../include/pipex_bonus.h"

void	ft_file_not_found(char *file)
{
	ft_putstr("No such file or directory!: ");
	ft_putstr(file);
	ft_putchar('\n');
}

int	ft_open_file(t_fd *fd, char *file, int b)
{
	if (b == 0)
	{
		fd->infile = open(file, O_RDONLY, 00644);
		return (fd->infile);
	}
	if (b == 1)
	{
		fd->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		return (fd->outfile);
	}
	if (b == 2)
	{
		fd->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 00644);
		return (fd->outfile);
	}
	return (0);
}

int	ft_checkargs(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	if (!envp || !envp[0])
	{
		ft_putstr("No environment variables found\n");
		return (-1);
	}
	while (i < argc)
	{
		if (!argv[i] || !argv[i][0])
		{
			ft_putstr("One of the arguments is empty or NULL\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_close(t_fd *fd)
{
	if (fd->isheredoc == 0)
	{
		if (fd->infile > 0)
			close(fd->infile);
	}
	if (fd->outfile > 0)
		close(fd->outfile);
	if (fd->pipefd[0] > 0)
		close(fd->pipefd[0]);
	if (fd->pipefd[1] > 0)
		close(fd->pipefd[1]);
	return (0);
}

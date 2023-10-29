/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:43 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/29 11:21:21 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"
#include "../include/pipex_bonus.h"

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

int	ft_checkargs(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!argv[i] || !argv[i][0])
		{
			ft_putstr(" : No such file of directory\n");
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

int	ft_not_here_doc(t_fd *fd, char **argv, int argc)
{
	fd->i = 2;
	if (ft_open_file(fd, argv[1], 0) < 0)
		return (ft_file_not_found(argv[1]), exit(-1), -1);
	if (ft_open_file(fd, argv[argc - 1], 1) < 0)
		return (close(fd->infile), exit(0), -1);
	if (dup2(fd->infile, STDIN_FILENO) == -1)
		return (close(fd->infile), close(fd->outfile), exit(0), -1);
	close(fd->infile);
	return (0);
}

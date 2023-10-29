/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:18:41 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/29 11:24:04 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/get_next_line.h"

// pipefd[0] read
// pipefd[1] write

// bash --posix

// STDIN_FILENO		0	/* Standard input.  */
// STDOUT_FILENO	1	/* Standard output.  */
// STDERR_FILENO	2	/* Standard error output.  */

void	ft_exec(char *cmd, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(cmd, ' ');
	if (!command)
		return (exit(0));
	if (ft_is_absolute(command[0]) == 0)
		return (ft_exec_abs(command, envp));
	path = ft_findcmdpath(command[0], envp, NULL, NULL);
	if (!path)
	{
		waitpid(0, NULL, 0);
		return (ft_freetab(command), exit(0));
	}
	if (execve(path, command, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd("\n", 2);
		ft_freetab(command);
		free(path);
		exit(0);
	}
}

void	ft_do_pipe(t_fd *fd, char *cmd, char **envp)
{
	pid_t	pid;

	if (pipe(fd->pipefd) == -1)
		return (ft_close(fd), exit(0));
	pid = fork();
	if (pid == -1)
		return (ft_close(fd), exit(0));
	if (pid == 0)
	{
		if (dup2(fd->pipefd[1], STDOUT_FILENO) == -1)
			return (ft_close(fd), exit(0));
		ft_close(fd);
		ft_exec(cmd, envp);
	}
	else
	{
		if (dup2(fd->pipefd[0], STDIN_FILENO) == -1)
			return (ft_close(fd), exit(0));
		wait(NULL);
		close(fd->pipefd[1]);
		if (fd->isheredoc == 0)
			close(fd->infile);
		close(fd->pipefd[0]);
	}
}

void	ft_here_doc2(t_fd *fd, char **argv)
{
	char	*ptr;

	ptr = NULL;
	close(fd->pipefd[0]);
	close(fd->outfile);
	while (1)
	{
		ptr = get_next_line(0);
		if (ft_strncmp(ptr, argv[2], ft_strlen(argv[2])) == 0
			&& ft_strlen(argv[2]) == ft_strlen(ptr) - 1)
		{
			return (free(ptr), close(fd->pipefd[1]), exit(0));
		}
		ft_putstr_fd(ptr, fd->pipefd[1]);
		free(ptr);
	}
	close(fd->pipefd[1]);
}

void	ft_here_doc(t_fd *fd, char **argv)
{
	pid_t	pid;

	fd->isheredoc = 1;
	if (pipe(fd->pipefd) == -1)
		return (close(fd->outfile), exit(0));
	pid = fork();
	if (pid == -1)
		return (ft_close(fd), exit(0));
	if (!pid)
	{
		ft_here_doc2(fd, argv);
	}
	else
	{
		if (dup2(fd->pipefd[0], STDIN_FILENO) == -1)
			return (ft_close(fd), exit(0));
		wait(NULL);
		close(fd->pipefd[1]);
		close(fd->pipefd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_fd	fd;

	fd.isheredoc = 0;
	if (argc < 5 || ft_checkargs(argc, argv) == -1)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		if (argc < 6)
			return (-1);
		fd.i = 3;
		if (ft_open_file(&fd, argv[argc - 1], 2) < 0)
			return (-1);
		ft_here_doc(&fd, argv);
	}
	else
		ft_not_here_doc(&fd, argv, argc);
	while (fd.i < argc - 2)
	{
		ft_do_pipe(&fd, argv[fd.i++], envp);
	}
	if (dup2(fd.outfile, STDOUT_FILENO) == -1)
		return (close(fd.outfile), -1);
	return (ft_close(&fd), ft_exec(argv[argc - 2], envp), wait(NULL), 0);
}

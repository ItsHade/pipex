/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:18:41 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/20 20:04:06 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/get_next_line.h"

// pipefd[0] read
// pipefd[1] write

void	ft_exec(char *cmd, char **envp)
{
	char	**command;
	char	*path;

	if (!cmd || !envp)
		exit(0);
	command = ft_split(cmd, ' ');
	if (!command)
		exit (0);
	path = ft_findcmdpath(command[0], envp);
	if (!path)
		exit(0);
	if (execve(path, command, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd("\n", 2);
		ft_freetab(command);
		exit(0);
	}
}

void	ft_do_pipe(char *cmd, char **envp)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		if (dup2(pipefd[1], 1) == -1)
			exit(0);
		close(pipefd[0]);
		ft_exec(cmd, envp);
	}
	else
	{
		if (dup2(pipefd[0], 0) == -1)
			exit(0);
		close(pipefd[1]);
	}
}

void	ft_here_doc2(char **argv, int *pipefd)
{
	char	*ptr;

	ptr = NULL;
	close(pipefd[0]);
	while (1)
	{
		ptr = get_next_line(0);
		if (ft_strncmp(ptr, argv[2], ft_strlen(argv[2])) == 0
			&& ft_strlen(argv[2]) == ft_strlen(ptr) - 1)
		{
			free(ptr);
			exit(0);
		}
		ft_putstr_fd(ptr, pipefd[1]);
		free(ptr);
	}
}

void	ft_here_doc(char **argv)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		ft_here_doc2(argv, pipefd);
	}
	else
	{
		if (dup2(pipefd[0], 0) == -1)
			exit(0);
		close(pipefd[1]);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;

	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		if (argc < 6)
			exit(0);
		i = 3;
		outfile = ft_open_file(argv[argc - 1], 2);
		ft_here_doc(argv);
	}
	else
	{
		i = 2;
		infile = ft_open_file(argv[1], 0);
		outfile = ft_open_file(argv[argc - 1], 1);
		if (dup2(infile, 0) == -1)
			exit(0);
	}
	while (i < argc - 2)
		ft_do_pipe(argv[i++], envp);
	return (ft_do_last(outfile), ft_exec(argv[argc - 2], envp), 0);
}

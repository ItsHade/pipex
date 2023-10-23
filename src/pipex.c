/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:22 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/22 15:33:24 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
		exit(0);
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

void	ft_child_process(char **argv, char **envp, int *pipefd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 00644);
	if (infile == -1)
	{
		ft_putstr("No such file or directory: ");
		ft_putstr(argv[1]);
		ft_putchar('\n');
		exit(0);
	}
	if (dup2(infile, 0) == -1)
		exit(0);
	if (dup2(pipefd[1], 1) == -1)
		exit(0);
	close(pipefd[0]);
	ft_exec(argv[2], envp);
}

void	ft_parent_process(char **argv, char **envp, int *pipefd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (outfile == -1)
		exit(0);
	if (dup2(outfile, 1) == -1)
		exit(0);
	if (dup2(pipefd[0], 0) == -1)
		exit(0);
	close(pipefd[1]);
	ft_exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5 || envp == NULL)
		return (0);
	if (pipe(pipefd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
		ft_child_process(argv, envp, pipefd);
	ft_parent_process(argv, envp, pipefd);
	return (0);
}

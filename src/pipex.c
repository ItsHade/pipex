/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:22 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/29 11:22:44 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// pipefd[0] read
// pipefd[1] write

void	ft_exec(char *cmd, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(cmd, ' ');
	if (!command)
		exit(-1);
	if (ft_is_absolute(command[0]) == 0)
		return (ft_exec_abs(command, envp));
	path = ft_findcmdpath(command[0], envp, NULL, NULL);
	if (!path)
	{
		ft_freetab(command);
		waitpid(0, NULL, 0);
		exit(-1);
	}
	if (execve(path, command, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd("\n", 2);
		ft_freetab(command);
		free(path);
		exit(-1);
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
		ft_closepipe(pipefd);
		exit(0);
	}
	if (dup2(infile, 0) == -1)
	{
		ft_closepipe(pipefd);
		close(infile);
		exit(0);
	}
	close(infile);
	if (dup2(pipefd[1], 1) == -1)
	{
		ft_closepipe(pipefd);
		exit(0);
	}
	ft_closepipe(pipefd);
	ft_exec(argv[2], envp);
}

void	ft_parent_process(char **argv, char **envp, int *pipefd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (outfile == -1)
	{
		ft_putstr("Open failed for outfile!\n");
		ft_closepipe(pipefd);
		exit(0);
	}
	if (dup2(outfile, 1) == -1)
	{
		ft_closepipe(pipefd);
		close(outfile);
		exit(0);
	}
	close(outfile);
	if (dup2(pipefd[0], 0) == -1)
	{
		ft_closepipe(pipefd);
		exit(0);
	}
	ft_closepipe(pipefd);
	ft_exec(argv[3], envp);
}

int	ft_checkarg(char **argv)
{
	if (!argv[1] || !argv[1][0] || !argv[4] || !argv[4][0])
	{
		ft_putstr(" : No such file of directory\n");
		return (-1);
	}
	if (!argv[2] || !argv[2][0] || !argv[3] || !argv[3][0])
	{
		ft_putstr(" : No such file of directory\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr("./pipex [infile] [cmd1] [cmd2] [outfile]\n");
		return (0);
	}
	if (ft_checkarg(argv) == -1)
		return (0);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (ft_closepipe(pipefd), 0);
	if (pid == 0)
		ft_child_process(argv, envp, pipefd);
	ft_parent_process(argv, envp, pipefd);
	return (0);
}

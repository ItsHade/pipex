/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:59:20 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/29 11:24:31 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**ft_removepathprefix(char **paths)
{
	int	i;
	int	a;
	int	len;

	a = 5;
	i = 0;
	if (paths == NULL)
		return (NULL);
	len = ft_strlen(paths[0]);
	while (a < len)
	{
		paths[0][i] = paths[0][a];
		i++;
		a++;
	}
	paths[0][i] = '\0';
	return (paths);
}

char	**ft_getpaths(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			paths = ft_split(envp[i], ':');
			if (!paths)
				return (NULL);
		}
		i++;
	}
	paths = ft_removepathprefix(paths);
	return (paths);
}

//donner 2 des variables definies en parametres mais vides
char	*ft_findcmdpath(char *cmd, char **envp, char *tmp, char *cmd_path)
{
	int		i;
	char	**paths;
	char	**command;

	i = -1;
	paths = ft_getpaths(envp);
	if (!paths)
		return (ft_file_not_found(cmd), NULL);
	command = ft_split(cmd, ' ');
	if (command == NULL)
		return (ft_freetab(paths), NULL);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_freetab(paths), ft_freetab(command), NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (ft_freetab(paths), ft_freetab(command), free(tmp), NULL);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_freetab(paths), ft_freetab(command), cmd_path);
		free(cmd_path);
	}
	return (ft_freetab(paths), ft_freetab(command), NULL);
}

int	ft_closepipe(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

void	ft_exec_abs(char **command, char **envp)
{
	if (execve(command[0], command, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd("\n", 2);
		ft_freetab(command);
		exit(-1);
	}
}

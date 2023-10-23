/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:59:20 by maburnet          #+#    #+#             */
/*   Updated: 2023/10/20 20:01:50 by maburnet         ###   ########.fr       */
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

char	*ft_findcmdpath(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	**command;
	char	*tmp;
	char	*cmd_path;

	i = -1;
	paths = ft_getpaths(envp);
	command = ft_split(cmd, ' ');
	if (paths == NULL || command == NULL)
		return (NULL);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (free(tmp), NULL);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_freetab(command), cmd_path);
		free(cmd_path);
	}
	return (ft_freetab(paths), ft_freetab(command), NULL);
}

int	ft_do_last(int outfile)
{
	if (dup2(outfile, 1) == -1)
		exit(0);
	return (0);
}

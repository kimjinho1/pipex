/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:18:17 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/13 19:13:12 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**get_env_path(char **envp)
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

static char	*get_cmd(char **path, char *cmd)
{
	int		i;
	char	*joined_cmd;
	char	*ret_cmd;

	i = 0;
	if (access(cmd, X_OK) != -1)
		return (cmd);
	joined_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		ret_cmd = ft_strjoin(path[i++], joined_cmd);
		if (access(ret_cmd, X_OK) != -1)
		{
			free(joined_cmd);
			return (ret_cmd);
		}
		free(ret_cmd);
	}
	free(joined_cmd);
	return (NULL);
}

void	execute(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	**cmd_arg;
	char	*cmd_path;

	i = 0;
	paths = get_env_path(envp);
	cmd_arg = ft_split(cmd, ' ');
	cmd_path = get_cmd(paths, cmd_arg[0]);
	if (!cmd_path)
	{
		while (paths[i])
			free(paths[i++]);
		free(paths);
		i = 0;
		while (cmd_arg[i])
			free(cmd_arg[i++]);
		free(cmd_arg);
		perror_exit("command error");
	}
	if (execve(cmd_path, cmd_arg, envp) == -1)
		perror_exit("execve error");
}

void	perror_exit(char *opt)
{
	perror(opt);
	exit(EXIT_FAILURE);
}

int	open_infile(char *path)
{
	int	infile;

	infile = open(path, O_RDONLY);
	if (infile == -1)
		perror_exit("infile error");
	return (infile);
}

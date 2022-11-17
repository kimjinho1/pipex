/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:16:54 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/18 02:22:13 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	perror_exit(char *opt)
{
	write(2, opt, ft_strlen(opt));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

static int	get_next_line(char **line)
{
	char	*buf;
	int		i;
	int		r;
	int		c;

	i = 0;
	r = 0;
	buf = (char *)malloc(50000);
	if (!buf)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buf[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buf[i] = '\0';
	*line = buf;
	return (r);
}

void	here_doc(char *limiter, char *path)
{
	int		here_doc_fd;
	char	*line;

	here_doc_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (get_next_line(&line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			return ;
		}
		write(here_doc_fd, line, ft_strlen(line));
		write(here_doc_fd, "\n", 1);
		free(line);
	}
	close(here_doc_fd);
}

char	**get_env_path(char **envp)
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*get_cmd(char **path, char *cmd)
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

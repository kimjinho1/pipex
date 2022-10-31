/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:16:54 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 03:03:05 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	**here_doc_shift(char **av, int n, char *path)
{
	int		i;
	int		size;
	char	**temp_av;
	
	i = 0;
	size = get_array_size(av) - n;
	temp_av = (char **)malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		temp_av[i] = ft_strdup(av[i + n]);
	temp_av[0] = path;
	temp_av[i] = NULL;
	return (temp_av);
}

void	here_doc(char *limiter, char *path)
{
	int		here_doc_fd;
	char	*line;

	here_doc_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (get_next_line(&line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			exit(EXIT_SUCCESS);
		write(here_doc_fd, line, ft_strlen(line));
		write(here_doc_fd, "\n", 1);
		free(line);
	}
}

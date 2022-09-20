/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:08:40 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/13 19:15:02 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_next_line(char **line)
{
	char	*buf;
	int		i;
	int		r;
	int		c;

	i = 0;
	r = 0;
	buf = (char *)malloc(10000);
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
	buf[i] = '\n';
	buf[++i] = '\0';
	*line = buf;
	free(buf);
	return (r);
}

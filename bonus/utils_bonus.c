/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:18:17 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 03:00:01 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	perror_exit(char *opt)
{
	write(2, opt, ft_strlen(opt));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	get_array_size(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	**shift(char **av, int n)
{
	int		i;
	int		size;
	char	**temp_av;
	
	i = -1;
	size = get_array_size(av) - n;
	temp_av = (char **)malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		temp_av[i] = ft_strdup(av[i + n]);
	temp_av[i] = NULL;
	return (temp_av);
}


void	free_array(char **arr, int n)
{
	int	i;

	i = n;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

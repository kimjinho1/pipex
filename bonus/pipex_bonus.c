/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:18:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/18 02:41:57 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	finish(int stdin_dup, int stdout_dup, int n)
{
	int	i;

	dup2(stdin_dup, 0);
	dup2(stdout_dup, 1);
	close(stdin_dup);
	close(stdout_dup);
	i = -1;
	while (++i < n)
		wait(NULL);
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	is_here_doc;
	int	stdin_dup;
	int	stdout_dup;

	if (ac < 5)
		perror_exit("argument error");
	i = 1;
	is_here_doc = 0;
	if (ft_strncmp(av[1], "here_doc", 8 + 1) == 0)
	{
		if (ac < 6)
			perror_exit("argument error");
		here_doc(av[2], "/tmp/here_doc");
		is_here_doc = 1;
		i = 2;
	}
	stdin_dup = dup(0);
	stdout_dup = dup(1);
	start_process(av, envp, ++i, is_here_doc);
	while (++i < ac - 2)
		middle_process(av, envp, i);
	last_process(av, envp, i, is_here_doc);
	finish(stdin_dup, stdout_dup, ac - 3 - is_here_doc);
	return (0);
}

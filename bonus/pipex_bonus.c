/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:18:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 04:52:05 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	finish(char **temp_av, int is_here_doc)
{
	while (wait(NULL) > 0)
		;
	free_array(temp_av, is_here_doc);
}

int	main(int ac, char **av, char **envp)
{
	char	**temp_av;
	int		is_here_doc;
	

	if (ac < 5)
		perror_exit("argument error");
	is_here_doc = 0;
	if (ft_strncmp(av[1], "here_doc", 8 + 1) == 0)
	{
		is_here_doc = 1;
		if (ac < 6)
			perror_exit("argument error");
		here_doc(av[2], "/tmp/here_doc");
		temp_av = here_doc_shift(av, 2, "/tmp/here_doc");
	}
	else
		temp_av = shift(av, 1);
	for (int i = 0; i < get_array_size(temp_av); i++)
		printf("temp_av[%d]: %s\n", i, temp_av[i]);
	process(temp_av, envp);
	printf("wait start\n");
	finish(temp_av, is_here_doc);
	printf("wait finish\n");
	return (0);
}

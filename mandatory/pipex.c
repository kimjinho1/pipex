/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:49:13 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 00:01:33 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		perror_exit("infile error");
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror_exit("dup2 error");
	close(infile);
	close(fd[0]);
	close(fd[1]);
	execute(av[2], envp);
}

void	parent_process(char **av, char **envp, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		perror_exit("outfile error");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror_exit("dup2 error");
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

	if (ac != 5)
		perror_exit("argument error");
	pid1 = fork();
	if (pid1 == -1)
		perror_exit("fork error");
	if (pipe(fd) == -1)
		perror_exit("pipe error");
	pid2 = fork();
	if (pid2 == -1)
		perror_exit("fork error");
	if (pid2 == 0)
		child_process(av, envp, fd);
	if (pid1 == 0)
		parent_process(av, envp, fd);
	close(fd[0]);
	close(fd[1]);
	while (wait(NULL) > 0)
		;
}

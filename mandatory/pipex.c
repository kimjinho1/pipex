/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:49:13 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/27 11:04:29 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **envp, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		perror_exit("infile error");
	close(fd[0]);
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror_exit("dup2 error");
	execute(av[2], envp);
}

void	parant_process(char **av, char **envp, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		perror_exit("outfile error");
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror_exit("dup2 error");
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		perror_exit("argument error");
	if (pipe(fd) == -1)
		perror_exit("pipe error");
	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	if (pid == 0)
		child_process(av, envp, fd);
	else
	{
		waitpid(pid, NULL, 0);
		parant_process(av, envp, fd);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:30:12 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 05:24:05 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	infile_process(char **temp_av, char **envp, int *fd)
{
	int	infile;

	printf("infile --- cmd: %s, infile: %s\n", temp_av[1], temp_av[0]);
	infile = open(temp_av[0], O_RDONLY);
	if (infile == -1)
		perror_exit("infile error");
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror_exit("dup2 error");
	close(infile);
	close(fd[0]);
	close(fd[1]);
	execute(temp_av[1], envp);
}

static void	middle_process(char *cmd, char **envp, int *fd)
{
	printf("mid --- cmd: %s\n", cmd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror_exit("dup2 error");
	close(fd[0]);
	close(fd[1]);
	execute(cmd, envp);
}

static void	outfile_process(char **temp_av, char **envp, int *fd)
{
	int	n;
	int outfile;

	n = get_array_size(temp_av) - 2;
	printf("outfile --- cmd: %s, outfile: %s\n", temp_av[n], temp_av[n + 1]);
	outfile = open(temp_av[n + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		perror_exit("outfile error");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror_exit("dup2 error");
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	execute(temp_av[n], envp);
}

static void	select_process(char **temp_av, char **envp, int *fd, int i)
{
	int	n;

	n = get_array_size(temp_av);
	if (i == 1)
		outfile_process(temp_av, envp, fd);
	else if (i == n - 2)
		infile_process(temp_av, envp, fd);
	else
		middle_process(temp_av[n - i - 1], envp, fd);
}

void	process(char **temp_av, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		i;
	int		n;

	i = 0;
	n = get_array_size(temp_av);
	if (pipe(fd) == -1)
		perror_exit("pipe error");
	while (++i < n - 1)
	{
		pid = fork();
		if (pid == -1)
			perror_exit("fork error");
		if (pid == 0)
		{
			printf("pid: %d, i: %d\n", pid, i);
			select_process(temp_av, envp, fd, i);
		}
	}
	close(fd[0]);
	close(fd[1]);
}

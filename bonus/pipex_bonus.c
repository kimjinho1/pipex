/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:18:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/10/28 20:50:48 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	here_doc(char *limiter)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror_exit("pipe error");
	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	if (pid == 0)
	{
		close(fd[0]);
		here_doc_write(limiter, fd);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
}

static void	infile_process(char *av, char **envp, int infile)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror_exit("pipe error");
	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infile);
		close(fd[0]);
		close(fd[1]);
		execute(av, envp);
	}	
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	child_process(char *av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror_exit("pipe error");
	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute(av, envp);
	}	
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

void	last_execute(int ac, char **av, char **envp)
{
	int	outfile;

	outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(outfile, STDOUT_FILENO);
	execute(av[ac - 2], envp);
}

int	main(int ac, char **av, char **envp)
{
	int	infile;
	int	i;

	if (ac < 5)
		perror_exit("argument error");
	if (ft_strncmp(av[1], "here_doc", 8 + 1) == 0)
	{
		if (ac < 6)
			perror_exit("argument error");
		here_doc(av[2]);
		i = 3;
		child_process(av[i++], envp);
	}
	else
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			perror_exit("infile error");
		i = 2;
		infile_process(av[i++], envp, infile);
	}
	while (i < ac - 2)
		child_process(av[i++], envp);
	last_execute(ac, av, envp);
}

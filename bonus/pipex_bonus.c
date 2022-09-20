/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:18:43 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/20 08:16:01 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_check(int ac, int *fd)
{
	if (ac < 6)
		perror_exit("argument error");
	if (pipe(fd) == -1)
		perror_exit("pipe error");
}

void	here_doc(char *limiter, int ac)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	here_doc_check(ac, &fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			dup2(fd[1], STDOUT_FILENO);
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		free(line);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	child_process(char *av, char **envp)
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
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp);
	}	
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			here_doc(av[2], ac);
			i = 3;
		}
		else
		{
			infile = open_infile(av[1]);
			dup2(infile, STDIN_FILENO);
			i = 2;
		}
		outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		while (i < ac - 2)
			child_process(av[i++], envp);
		dup2(outfile, STDOUT_FILENO);
		execute(av[ac - 2], envp);
	}
	perror_exit("argument error");
}

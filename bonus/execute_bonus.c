/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:33:03 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/18 02:37:57 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	**cmd_arg;
	char	*cmd_path;

	i = 0;
	paths = get_env_path(envp);
	cmd_arg = ft_split(cmd, ' ');
	cmd_path = get_cmd(paths, cmd_arg[0]);
	if (!cmd_path)
	{
		while (paths[i])
			free(paths[i++]);
		free(paths);
		i = 0;
		while (cmd_arg[i])
			free(cmd_arg[i++]);
		free(cmd_arg);
		perror_exit("command error");
	}
	if (execve(cmd_path, cmd_arg, envp) == -1)
		perror_exit("execve error");
}

static void	set_start_stdin(char **av, int is_here_doc)
{
	int	infile;

	if (is_here_doc == 1)
		infile = open("/tmp/here_doc", O_RDONLY);
	else
		infile = open(av[1], O_RDONLY);
	if (infile == -1)
		perror_exit("infile error");
	if (dup2(infile, STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	close(infile);
	if (is_here_doc == 1)
		unlink("/tmp/here_doc");
}

void	start_process(char **av, char **envp, int i, int is_here_doc)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror_exit("pipe error");
	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	if (pid == 0)
	{
		set_start_stdin(av, is_here_doc);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror_exit("dup2 error");
		close(fd[0]);
		close(fd[1]);
		execute(av[i], envp);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	close(fd[0]);
	close(fd[1]);
}

void	middle_process(char **av, char **envp, int i)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror_exit("pipe error");
	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror_exit("dup2 error");
		close(fd[0]);
		close(fd[1]);
		execute(av[i], envp);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror_exit("dup2 error");
	close(fd[0]);
	close(fd[1]);
}

void	last_process(char **av, char **envp, int i, int is_here_doc)
{
	pid_t	pid;
	int		outfile;

	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	if (pid == 0)
	{
		if (is_here_doc == 1)
			outfile = open(av[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			outfile = open(av[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			perror_exit("outfile error");
		if (dup2(outfile, STDOUT_FILENO) == -1)
			perror_exit("dup2 error");
		execute(av[i], envp);
	}
}

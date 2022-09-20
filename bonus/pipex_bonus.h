/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:17:44 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/13 19:13:48 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include "../ft_printf/ft_printf.h"

void	perror_exit(char *opt);
void	execute(char *cmd, char **envp);
int		open_infile(char *path);

int		get_next_line(char **line);

void	here_doc(char *limiter, int ac);
void	child_process(char *av, char **envp);

#endif

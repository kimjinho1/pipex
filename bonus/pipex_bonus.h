/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:17:44 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 03:34:09 by jinhokim         ###   ########.fr       */
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
int	    get_array_size(char **av);
char	**shift(char **av, int n);
void	free_array(char **arr, int n);

void	here_doc(char *limiter, char *path);
char	**here_doc_shift(char **av, int n, char *path);

void	execute(char *cmd, char **envp);

void	process(char **temp_av, char **envp);

#endif

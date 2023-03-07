/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:32:27 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/02 16:54:21 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../reworked-libft/libft.h"

typedef	struct s_data
{
	int		*status;
	int		fd[2];
	char	**paths;
	char	**args1;
	char	**args2;
	char	*cmd1;
	char	*cmd2;
	char	*prog1;
	char	*prog2;
	pid_t	child1;
	pid_t	child2;
}				t_data;

void	data_init(t_data *d, char **argv, char **envp);

#endif
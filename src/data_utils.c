/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:14:55 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/02 10:16:51 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	data_init(t_data *d, char **argv, char **envp)
{
	char	*path;		// line of the env command that has the paths
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5))
			path = envp[i];
	if (!path)
		exit (EXIT_FAILURE);
	i = -1;
	d->paths = ft_split(path, ':');
	while (d->paths[++i])
		ft_strjoin(d->paths[i], "/");
	d->cmd1 = ft_strdup(argv[2]);
	d->cmd2 = ft_strdup(argv[3]);
	if (!d->cmd1 || !d->cmd2)
		exit (EXIT_FAILURE);
}
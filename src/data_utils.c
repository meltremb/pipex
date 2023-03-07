/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:14:55 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/07 16:43:14 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free(t_data *d)
{
	if (d->paths)
		ft_free_array((void ***)&(d->paths));
	if (d->args1)
		ft_free_array((void ***)&(d->args1));
	if (d->args2)
		ft_free_array((void ***)&(d->args2));
}

void	ft_close_all(t_data *d)
{
	close(d->end[0]);
	close(d->end[1]);
	close(d->fd2);
	close(d->fd1);
}

void	arg_check(char **argv)
{
	if (!argv[1][0] || !argv[4][0])
		ft_exit("Invalid File arguments");
	if (!argv[2][0] || !argv[3][0])
		ft_exit("Invalid command arguments");
}

void	data_init(t_data *d, char **argv, char **envp)
{
	char	*path;
	int		i;
	char	*temp;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
	if (!path)
		exit (EXIT_FAILURE);
	i = -1;
	d->paths = ft_split(path, ':');
	while (d->paths[++i])
	{
		temp = d->paths[i];
		d->paths[i] = ft_strjoin(temp, "/");
		ft_free_null((void **)&temp);
	}
	d->args1 = ft_split(argv[2], ' ');
	d->args2 = ft_split(argv[3], ' ');
	d->cmd1 = d->args1[0];
	d->cmd2 = d->args2[0];
	if (!d->cmd1 || !d->cmd2)
		exit (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:14:55 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/07 13:29:48 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*alpha_copy(char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	while (ft_isalpha(s[i]) != 0)
		i++;
	ptr = malloc(i * (sizeof(char)));
	if (!ptr)
		return (NULL);
	i = -1;
	while (ft_isalpha(s[++i]) != 0)
		ptr[i] = s[i];
	ptr[i] = '\0';
	return (ptr);
}

char	**args(char *argv)
{
	char	**array;

	array = ft_split(argv, ' ');
	if (!array[1])
		array[1] = NULL;
	return (array);
}

void	data_init(t_data *d, char **argv, char **envp)
{
	char	*path;
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
	if (!path)
		exit (EXIT_FAILURE);
	i = -1;
	d->paths = ft_split(path, ':');
	while (d->paths[++i])
		d->paths[i] = ft_strjoin(d->paths[i], "/");
	d->cmd1 = alpha_copy(argv[2]);
	d->cmd2 = alpha_copy(argv[3]);
	d->args1 = args(argv[2]);
	d->args2 = args(argv[3]);
	if (!d->cmd1 || !d->cmd2)
		exit (EXIT_FAILURE);
}
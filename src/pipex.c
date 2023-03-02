/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:08 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/02 10:13:57 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child_one(t_data *d, char **envp)
{
	int	i;

	i = -1;
	while (d->paths[++i])
		if (access(ft_strjoin(d->paths[i], d->cmd1), F_OK))
			d->status = execve(d->paths[i], &d->cmd1, envp);
	if (d->status == -1)
		return (EXIT_FAILURE);
	return (0);
}

int	child_two(t_data *d, char **envp)
{
	int	i;

	i = -1;
	while (d->paths[++i])
		if (access(ft_strjoin(d->paths[i], d->cmd2), F_OK))
			d->status = execve(d->paths[i], &d->cmd2, envp);
	if (d->status == -1)
		return (EXIT_FAILURE);
	return (0);
}

void	pipex(t_data *d, char **envp)
{
	pipe(d->end);
	d->child1 = fork();
	if (d->child1 < 0)
		return (perror("Fork: "));
	if (d->child1 == 0)
		child_one(d, envp);
	d->child2 = fork();
	if (d->child2 < 0)
		return (perror("Fork: "));
	if (d->child2 == 0)	
		child_two(d, envp);
	close(d->end[0]);
	close(d->end[1]);
	waitpid(d->child1, &d->status, 0);
	waitpid(d->child2, &d->status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data d;

	if (argc != 5)
		return (0);
	d.f1 = open(argv[1], O_RDONLY);
	d.f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d.f1 < 0 || d.f2 < 0)
		return (-1);
	data_init(&d, argv, envp);
	pipex(&d, envp);
	return (0);
}
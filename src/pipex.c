/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:08 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/07 13:40:24 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child(t_data *d, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	dup2(d->fd1, STDIN_FILENO);
	dup2(d->end[1], STDOUT_FILENO);
	close(d->end[0]);
	while (d->paths[++i])
	{
		cmd = ft_strjoin(d->paths[i], d->cmd1);
		if (access(cmd, F_OK | X_OK) == 0)
			execve(cmd, d->args1, envp);
		else
			free(cmd);
	}
	if (execve(cmd, d->args1, envp) == -1)
		perror("child");
	return (EXIT_FAILURE);
}

int	parent(t_data *d, char **envp)
{
	int		i;
	char	*cmd;

	waitpid(d->child, d->status, WEXITED | WSTOPPED);
	i = -1;
	dup2(d->end[0], STDIN_FILENO);
	dup2(d->fd2, STDOUT_FILENO);
	close(d->end[1]);
	while (d->paths[++i])
	{
		cmd = ft_strjoin(d->paths[i], d->cmd2);
		if (access(cmd, F_OK | X_OK) == 0)
			execve(cmd, d->args2, envp);
		else
			free(cmd);
	}
	if (execve(cmd, d->args2, envp) == -1)
		perror("parent");
	return (EXIT_FAILURE);
}

void	pipex(t_data *d, char **envp)
{
	pipe(d->end);
	d->parent = fork();
	if (d->parent < 0)
		return (perror("Fork: "));
	if (!d->parent)
		child(d, envp);
	else
		parent(d, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data d;

	if (argc != 5)
		return (0);
	d.fd1 = open(argv[1], O_RDONLY);
	d.fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d.fd1 < 0 || d.fd2 < 0)
		return (-1);
	data_init(&d, argv, envp);
	pipex(&d, envp);
	return (0);
}
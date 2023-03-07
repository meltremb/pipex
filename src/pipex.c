/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:08 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/02 17:05:34 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// ./pipex file1 "cat -e" "grep -i lol" file2

int	child_one(t_data *d, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	dup2(d->fd[0], STDIN_FILENO);
	close(d->fd[1]);
	while (d->paths[++i])
	{
		cmd = ft_strjoin(d->paths[i], d->cmd1);
		if (access(cmd, F_OK | X_OK) == 0)
			execve(cmd, d->args1, envp);
		else
			free(cmd);
	}
	printf("child one complete\n");
	if (execve(cmd, d->args1, envp) == -1)
		perror("child_one");
	printf("child one complete\n");
	return (EXIT_FAILURE);
}

int	child_two(t_data *d, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	dup2(d->fd[1], STDOUT_FILENO);
	close(d->fd[0]);
	while (d->paths[++i])
	{
		cmd = ft_strjoin(d->paths[i], d->cmd2);
		if (access(cmd, F_OK | X_OK) == 0)
			execve(cmd, d->args2, envp);
		else
			free(cmd);
	}
	if (execve(cmd, d->args2, envp) == -1)
		perror("child_one");
	printf("child two complete\n");
	return (EXIT_FAILURE);
}

void	pipex(t_data *d, char **envp)
{
	pipe(d->fd);
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
	close(d->fd[0]);
	close(d->fd[1]);
	waitpid(d->child1, d->status, WEXITED | WSTOPPED);
	waitpid(d->child2, d->status, WEXITED | WSTOPPED);
	exit (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data d;

	if (argc != 5)
		return (0);
	d.fd[0] = open(argv[1], O_RDONLY);
	d.fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d.fd[0] < 0 || d.fd[1] < 0)
		return (-1);
	data_init(&d, argv, envp);
	pipex(&d, envp);
	return (0);
}
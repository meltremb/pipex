/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:08 by meltremb          #+#    #+#             */
/*   Updated: 2023/03/20 08:54:26 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child_one(t_data *d, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	dup2(d->fd1, STDIN_FILENO);
	dup2(d->end[1], STDOUT_FILENO);
	ft_close(d);
	while (d->paths[++i])
	{
		cmd = ft_strjoin(d->paths[i], d->cmd1);
		if (access(cmd, F_OK | X_OK) == 0)
			execve(cmd, d->args1, envp);
		else
			free(cmd);
	}
	ft_free(d);
	if (cmd)
		free(cmd);
	if (execve(cmd, d->args1, envp) == -1)
		perror("child1");
	return (EXIT_FAILURE);
}

int	child_two(t_data *d, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	dup2(d->end[0], STDIN_FILENO);
	dup2(d->fd2, STDOUT_FILENO);
	ft_close(d);
	while (d->paths[++i])
	{
		cmd = ft_strjoin(d->paths[i], d->cmd2);
		if (access(cmd, F_OK | X_OK) == 0)
			execve(cmd, d->args2, envp);
		else
			free(cmd);
	}
	ft_free(d);
	if (cmd)
		free(cmd);
	if (execve(cmd, d->args2, envp) == -1)
		perror("child2");
	return (EXIT_FAILURE);
}

void	pipex(t_data *d, char **envp)
{
	pipe(d->end);
	d->child1 = fork();
	if (d->child1 < 0)
		return (perror("Fork: "));
	if (!d->child1)
		child_one(d, envp);
	d->child2 = fork();
	if (d->child2 < 0)
		return (perror("Fork: "));
	if (!d->child2)
		child_two(d, envp);
	ft_close(d);
	waitpid(d->child1, d->status, 0);
	waitpid(d->child2, d->status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;

	if (argc != 5)
		ft_exit("Wrong amount of arguments");
	arg_check(argv);
	d.fd1 = open(argv[1], O_RDONLY);
	d.fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (d.fd1 < 0 || d.fd2 < 0)
	{
		ft_close_all(&d);
		ft_exit("No input file");
	}
	data_init(&d, argv, envp);
	pipex(&d, envp);
	ft_free(&d);
	ft_close_all(&d);
	ft_exit("");
}

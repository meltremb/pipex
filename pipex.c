/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:38:08 by meltremb          #+#    #+#             */
/*   Updated: 2023/02/27 12:58:37 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4]), O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	pipex(f1, f2, argv, envp);
	return (0);
}
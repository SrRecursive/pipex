/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:49:56 by ribana-b          #+#    #+#             */
/*   Updated: 2023/10/26 00:06:01 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;

	status = 0;
	if (pipe(pipefd) < 0)
		ft_error_message("pipe");
	pid = fork();
	if (pid < 0)
		ft_error_message("fork");
	else if (pid == 0)
		ft_first_child_process(argv, envp, pipefd);
	else
	{
		waitpid(pid, &status, 0);
		status = ft_parent_process(argv, envp, pipefd, argc);
	}
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	status;

	if (argc != 5)
		return (0);
	status = pipex(argc, argv, envp);
	return (status);
}

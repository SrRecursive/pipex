/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:49:56 by ribana-b          #+#    #+#             */
/*   Updated: 2023/11/25 16:19:18 by ribana-b         ###   ########.fr       */
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
	if (pid == 0)
		ft_first_child_process(argv, envp, pipefd);
	else
	{
		waitpid(pid, &status, WNOHANG);
		status = ft_parent_process(argv, envp, pipefd, argc);
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	int	status;

	if (argc != 5)
		return (1);
	for (int i = 0; argv[i]; i++)
		printf("%s\n", argv[i]);
	status = pipex(argc, argv, envp);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:49:56 by ribana-b          #+#    #+#             */
/*   Updated: 2023/11/24 10:00:54 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_argv_parser(int argc, char **argv)
{
	int	counter;

	counter = 2;
	while (argv[argc - counter] && (argc - counter) > 1)
	{
		if (!argv[argc - counter][0])
			return (1);
		counter++;
	}
	return (0);
}

int	pipex(int argc, char **argv, char **envp)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;

	if (ft_argv_parser(argc, argv) != 0)
		ft_error_message("Empty command");
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
	status = pipex(argc, argv, envp);
	return (status);
}

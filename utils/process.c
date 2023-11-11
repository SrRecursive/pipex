/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:00:48 by ribana-b          #+#    #+#             */
/*   Updated: 2023/10/27 08:00:50 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_first_child_process(char **argv, char **envp, int *fd)
{
	int	infilefd;

	infilefd = open(argv[1], O_RDONLY, 0644);
	if (infilefd < 0)
		ft_error_message("open");
	close(fd[0]);
	if (dup2(infilefd, STDIN_FILENO) < 0)
		ft_error_message("dup2");
	close(infilefd);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		ft_error_message("dup2");
	close(fd[1]);
	ft_execute_command(argv[2], envp);
	return ;
}

void	ft_last_child_process(char **argv, char **envp, int *fd, int argc)
{
	int	outfilefd;

	outfilefd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfilefd < 0)
		ft_error_message("open");
	if (dup2(fd[0], STDIN_FILENO) < 0)
		ft_error_message("dup2");
	close(fd[0]);
	if (dup2(outfilefd, STDOUT_FILENO) < 0)
		ft_error_message("dup2");
	close(outfilefd);
	ft_execute_command(argv[argc - 2], envp);
}

int	ft_parent_process(char **argv, char **envp, int *fd, int argc)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	close(fd[1]);
	if (pid < 0)
		ft_error_message("fork");
	else if (pid == 0)
		ft_last_child_process(argv, envp, fd, argc);
	else
	{
		waitpid(pid, &status, 0);
		close(fd[0]);
	}
	return (status);
}

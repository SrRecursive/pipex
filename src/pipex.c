/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:49:56 by ribana-b          #+#    #+#             */
/*   Updated: 2023/10/22 15:44:39 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_command(char *argv, char **envp)
{
	char	**command;
	char	*path;
	int		i;

	i = 0;
	command = ft_split(argv, ' ');
	path = find_path(command[0], envp);
	if (!path)
	{
		while (command[i])
			free(command[i++]);
		free(command);
		error_message("path");
	}
	if (execve(path, command, envp) == -1)
		error_message("execve");
	return ;
}

void	child(char **argv, char **envp, int *fd)
{
	int		infile;

	infile = open(argv[1], O_RDONLY, 0644);
	if (infile == -1)
		error_message("open");
	close(fd[0]);
	if (dup2(infile, STDIN_FILENO) == -1)
		error_message("dup2");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_message("dup2");
	execute_command(argv[2], envp);
	return ;
}

void	parent(char **argv, char **envp, int *fd)
{
	int		outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		error_message("open");
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_message("dup2");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_message("dup2");
	execute_command(argv[3], envp);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("\033[33mUsage: ", 1);
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n\033", 1);
		return (1);
	}
	if (pipe(fd) == -1)
		error_message("pipe");
	pid = fork();
	if (pid == -1)
		error_message("fork");
	if (pid == 0)
		child(argv, envp, fd);
	parent(argv, envp, fd);
	return (0);
}

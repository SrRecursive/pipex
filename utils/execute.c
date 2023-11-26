/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 07:57:30 by ribana-b          #+#    #+#             */
/*   Updated: 2023/11/26 12:10:52 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*ft_strjoin_pipex(char *str, char *str2)
{
	char	*newstr;
	int		counter;
	int		counter2;

	counter = ft_strlen(str);
	counter2 = ft_strlen(str2);
	newstr = (char *)malloc((counter + counter2 + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	newstr[counter + counter2] = '\0';
	while (counter2-- > 0)
		newstr[counter + counter2] = str2[counter2];
	while (counter-- > 0)
		newstr[counter] = str[counter];
	free(str);
	return (newstr);
}

static void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i++] = NULL;
	}
	free(path);
	path = NULL;
	return ;
}

char	*ft_find_path(char *command, char **envp)
{
	int		i;
	char	**path;
	char	*path_command;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0 && envp[i] != NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		path_command = ft_strjoin(path[i], "/");
		path_command = ft_strjoin_pipex(path_command, command);
		if (access(path_command, F_OK) == 0)
		{
			ft_free_path(path);
			return (path_command);
		}
		free(path_command);
		i++;
	}
	ft_free_path(path);
	return (NULL);
}

void	ft_execute_command(char *argv, char **envp)
{
	char	**command;
	char	*path;
	int		i;

	i = 0;
	command = ft_split(argv, ' ');
	if (ft_strncmp(command[0], "/bin/", 5) == 0
		|| ft_strncmp(command[0], "/usr/", 5) == 0)
		if (execve(command[0], command, envp) == -1)
			ft_error_message("execve");
	path = ft_find_path(command[0], envp);
	if (!path)
	{
		while (command[i])
		{
			free(command[i]);
			command[i++] = NULL;
		}
		free(command);
		command = NULL;
		ft_error_message("path");
	}
	if (execve(path, command, envp) == -1)
		ft_error_message("execve");
	return ;
}

void	ft_execute_space(void)
{
	char	**cmdspace;
	char	*space;

	cmdspace = ft_split(" ", '\t');
	space = ft_strdup(" ");
	if (execve(space, cmdspace, NULL) == -1)
		ft_error_message("execve");
}

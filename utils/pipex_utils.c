/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:32 by ribana-b          #+#    #+#             */
/*   Updated: 2023/10/22 15:46:27 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_message(const char *str)
{
	if (ft_strncmp(str, "pipe", 4) == 0)
		perror("pipe");
	else if (ft_strncmp(str, "fork", 4) == 0)
		perror("fork");
	else if (ft_strncmp(str, "open", 4) == 0)
		perror("open");
	else if (ft_strncmp(str, "execve", 6) == 0)
		perror("execve");
	exit(EXIT_FAILURE);
}

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

static void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	return ;
}

char	*find_path(char *command, char **envp)
{
	int		i;
	char	**path;
	char	*path_command;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		path_command = ft_strjoin(path[i], "/");
		path_command = ft_strjoin_pipex(path_command, command);
		if (access(path_command, F_OK) == 0)
		{
			free_path(path);
			return (path_command);
		}
		free(path_command);
		i++;
	}
	free_path(path);
	return (NULL);
}

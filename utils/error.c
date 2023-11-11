/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:32 by ribana-b          #+#    #+#             */
/*   Updated: 2023/10/23 09:14:33 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error_message(const char *str)
{
	if (ft_strncmp(str, "pipe", 4) == 0)
		perror("pipe");
	else if (ft_strncmp(str, "fork", 4) == 0)
		perror("fork");
	else if (ft_strncmp(str, "open", 4) == 0)
		perror("open");
	else if (ft_strncmp(str, "execve", 6) == 0)
		perror("execve");
	else if (ft_strncmp(str, "dup", 3) == 0)
		perror("dup");
	else if (ft_strncmp(str, "dup2", 4) == 0)
		perror("dup2");
	exit(EXIT_FAILURE);
}

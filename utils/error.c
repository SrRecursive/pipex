/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:33:32 by ribana-b          #+#    #+#             */
/*   Updated: 2023/11/24 10:01:30 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error_message(const char *str)
{
	perror(str);
	if (ft_strncmp(str, "execve", 6) == 0)
		exit(127);
	if (ft_strncmp(str, "path", 4) == 0)
		exit(127);
	exit(EXIT_FAILURE);
}

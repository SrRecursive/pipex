/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:14:51 by ribana-b          #+#    #+#             */
/*   Updated: 2023/11/26 11:44:09 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_argv_parser(char *argv)
{
	int	counter;

	if (!argv)
		return (-1);
	counter = 0;
	if (ft_strncmp(argv, "/usr/", 5) == 0 || ft_strncmp(argv, "/bin/", 5) == 0)
	{
		while(argv[counter] != ' ' && argv[counter])
			counter++;
		if (!argv[counter])
			return (1);
		return (0);
	}
	while (argv[counter] && argv[counter] == ' ')
	{
		if (argv[counter] != ' ')
			break ;
		counter++;
	}
	if (argv[counter] != ' ' && argv[counter])
		return (1);
	return (0);
}

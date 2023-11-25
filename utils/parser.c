/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:14:51 by ribana-b          #+#    #+#             */
/*   Updated: 2023/11/25 23:37:26 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_argv_parser(char *argv)
{
	int	counter;

	if (!argv)
		return (-1);
	counter = 0;
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

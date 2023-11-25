/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:42:31 by ribana-b          #+#    #+#             */
/*   Updated: 2023/11/25 23:41:04 by ribana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* <--Libraries Section--> */

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../BFL/include/bfl.h"

/* <--Functions Section--> */

int		pipex(int argc, char **argv, char **envp);
void	ft_error_message(const char *str);
void	ft_execute_command(char *argv, char **envp);
void	ft_first_child_process(char **argv, char **envp, int *fd);
void	ft_last_child_process(char **argv, char **envp, int *fd, int argc);
int		ft_parent_process(char **argv, char **envp, int *fd, int argc);
char	*ft_find_path(char *command, char **envp);
int		ft_argv_parser(char *argv);

#endif

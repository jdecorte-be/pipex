/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:31:27 by jdecorte          #+#    #+#             */
/*   Updated: 2021/12/07 16:50:28 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>
# define STDERR 2

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	**av;
	char	**env;
	char	**cmdac;
	char	*path;
	int		p_fd[2];
	char	*exec;
	char	**cmd;
	char	**allpath;
}		t_pipex;

void	puterror(char *str);

#endif // !PIPEX_H
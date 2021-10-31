/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:09:15 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/31 18:40:05 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	puterror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR, &str[i], 1);
}

void	p_child1(t_pipex *tab)
{
	int	i;

	tab->cmd = ft_split(tab->av[2], ' ');
	dup2(tab->fd1, 0);
	dup2(tab->p_fd[1], 1);
	close(tab->p_fd[0]);
	close(tab->fd1);
	i = -1;
	while (tab->allpath[++i])
	{
		tab->allpath[i] = ft_strjoin(tab->allpath[i], "/");
		tab->exec = ft_strjoin(tab->allpath[i], tab->cmd[0]);
		free(tab->allpath[i]);
		if (access(tab->exec, X_OK) == 0)
			break ;
		free(tab->exec);
	}
	execve(tab->exec, &tab->cmd[0], tab->env);
	puterror(tab->av[2]);
	puterror(": command not found\n");
	exit(127);
}

void	p_child2(t_pipex *tab)
{
	int		status;
	int		i;

	tab->cmd = ft_split(tab->av[3], ' ');
	waitpid(-1, &status, 0);
	dup2(tab->p_fd[0], 0);
	dup2(tab->fd2, 1);
	close(tab->p_fd[1]);
	close(tab->fd2);
	i = -1;
	while (tab->allpath[++i])
	{
		tab->allpath[i] = ft_strjoin(tab->allpath[i], "/");
		tab->exec = ft_strjoin(tab->allpath[i], tab->cmd[0]);
		free(tab->allpath[i]);
		if (access(tab->exec, X_OK) == 0)
			break ;
		free(tab->exec);
	}
	execve(tab->exec, &tab->cmd[0], tab->env);
	puterror(tab->av[3]);
	puterror(": command not found\n");
	exit(127);
}

void	pipex(t_pipex *tab)
{
	pid_t	pid;
	int		status;

	pipe(tab->p_fd);
	pid = fork();
	if (pid < 0)
		return (perror("fork:"));
	if (pid == 0)
		p_child1(tab);
	if (pid != 0)
		p_child2(tab);
	close(tab->p_fd[0]);
	close(tab->p_fd[1]);
	waitpid(pid, &status, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:09:15 by jdecorte          #+#    #+#             */
/*   Updated: 2021/12/07 16:52:00 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// error handler
void	puterror(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR, &str[i], 1);
}

// find path and exec
void exec(t_pipex *tab, char *cmd)
{
	int i;
	char **args = ft_split(cmd, ' ');

	i = -1;
	while (tab->allpath[++i])
	{
		tab->allpath[i] = ft_strjoin(tab->allpath[i], "/");
		tab->exec = ft_strjoin(tab->allpath[i], args[0]);
		free(tab->allpath[i]);
		if (access(tab->exec, X_OK) == 0)
			break ;
		free(tab->exec);
	}
	execve(tab->exec, &args[0], tab->env);
	puterror(cmd);
	puterror(": command not found\n");;
	exit(127);
}

void	pipex(t_pipex *tab, char *cmd)
{
	pid_t	pid;

	pipe(tab->p_fd);
	pid = fork();
	if (pid < 0)
		return (perror("fork:"));

	// first
	if (pid)
	{
		dup2(tab->p_fd[0], 0);
		dup2(tab->fd2, 1);
		close(tab->p_fd[1]);
		close(tab->fd2);
		waitpid(pid, NULL, 0);
	}
	// second
	else
	{
		dup2(tab->fd1, 0);
		dup2(tab->p_fd[1], 1);
		close(tab->p_fd[0]);
		close(tab->fd1);
		exec(tab, cmd);
	}
}

void	init_tab(t_pipex *tab, int ac)
{
	int	j;

	tab->fd1 = open(tab->av[1], O_RDONLY);
	tab->fd2 = open(tab->av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tab->fd1 < 0)
	{
		perror(tab->av[1]);
		if (tab->fd2 < 0)
			perror(tab->av[4]);
		exit(1);
	}
	j = -1;
	while (tab->env[++j])
		if (ft_strnstr(tab->env[j], "PATH", ft_strlen(tab->env[j])) != NULL)
			tab->path = tab->env[j];
	tab->path = ft_substr(tab->path, 5, ft_strlen(tab->path));
	tab->allpath = ft_split(tab->path, ':');
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*tab;

	if (ac >= 5)
	{
		tab = malloc(sizeof(t_pipex));
		tab->env = env;
		tab->av = av;
		init_tab(tab, ac);
		int i = 3;
		while(i < ac - 2)
			pipex(tab, av[i++]);
		exec(tab, av[i]);
		close(tab->fd1);
		close(tab->fd2);
	}
	else
		puterror("$RES_REAL: ambiguous redirect\n");
	exit(1);
}

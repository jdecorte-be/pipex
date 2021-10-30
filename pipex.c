/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:09:15 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/30 16:59:53 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void puterror(char *str)
{
	int i = 0;
	while (str[i])
	{
		write(STDERR, &str[i], 1);
		i++;
	}
}

void geterror(t_pipex *tab)
{
	// if ()
	(void)tab;
	fprintf(stderr, "%d \n", tab->cmd1);
	fprintf(stderr, "%d \n", tab->cmd2);
	// puterror(": command not found\n");

	exit(0);
}

void p_child1(t_pipex *tab)
{
	char	**cmd1;
	char	*cmd;
	int		i;
	char	**allpaths = ft_split(tab->path, ':');

	cmd1 = ft_split(tab->av[2], ' ');
	dup2(tab->fd1, 0);
	dup2(tab->p_fd[1], 1);
	close(tab->p_fd[0]);
	close(tab->fd1);

	i = -1;
	while (allpaths[++i])
	{
		allpaths[i] = ft_strjoin(allpaths[i], "/");
		cmd = ft_strjoin(allpaths[i], cmd1[0]);
		if (access(cmd, X_OK) == 0)
			break ;
		free(cmd);
	}
	execve(cmd, &cmd1[0], tab->env);
	exit(-1);
}

void p_child2(t_pipex *tab)
{
	int		status;
	char	**cmd1 = ft_split(tab->av[3], ' ');

	char	**allpaths = ft_split(tab->path, ':');

	waitpid(-1, &status, 0);
	dup2(tab->p_fd[0], 0);
	dup2(tab->fd2, 1);
	close(tab->p_fd[1]);
	close(tab->fd2);
	// execve for each command

	char *cmd;
	int i = -1;
	while (allpaths[++i])
	{
		allpaths[i] = ft_strjoin(allpaths[i], "/");
		cmd = ft_strjoin(allpaths[i], cmd1[0]);
		if (access(cmd, X_OK) == 0)
			break ;
		free(cmd);
	}
	execve(cmd, &cmd1[0], tab->env);
	exit(-1);
}


void pipex(t_pipex *tab)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int 	status;

	pipe(p_fd);
	tab->p_fd = p_fd;

	pid1 = fork();
	if (pid1 < 0)
		return perror("\e[0;31mFork error : ");
	if (pid1 == 0)
		p_child1(tab);
	pid2 = fork();
	if (pid2 < 0)
		return perror("\e[0;31mFork error : ");
	if (pid2 == 0)
		p_child2(tab);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}

int main(int ac, char *av[], char *env[])
{
	if (ac == 5)
	{
		t_pipex		*tab;
		int			file1;
		int			file2;
		file1 = 0;
		file2 = 0;
		tab = ft_calloc(1, sizeof(t_pipex));
		tab->cmd1 = 0;
		tab->cmd2 = 0;
		tab->fd1 = open(av[1], O_RDONLY);
		tab->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (tab->fd1 < 0)
		{
			perror(av[1]);
			if (tab->fd2 < 0)
				perror(av[4]);
			exit(1);
		}
		tab->env = env;
		tab->av = av;
		int j = -1;
		while (tab->env[++j])
		{
			if (ft_strnstr(tab->env[j], "PATH", ft_strlen(tab->env[j])) != NULL)
				tab->path = tab->env[j];
		}
		tab->path = ft_substr(tab->path, 5, ft_strlen(tab->path));

		pipex(tab);
		close(file1);
		close(file2);
		geterror(tab);
	}
	else
	{
		puterror("$RES_REAL: ambiguous redirect\n");
		exit(1);
	}
	exit(0);
}

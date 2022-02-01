/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: decortejohn <decortejohn@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:09:15 by jdecorte          #+#    #+#             */
/*   Updated: 2022/02/01 18:23:16 by decortejohn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void here_doc(char *av, t_pipex *tab)
{
	char *ret;
	int fd;
	int p_fd[2];
	pid_t pid;

	pipe(p_fd);
	pid = fork();
	if(!pid)
	{
		close(p_fd[0]);
		while(1)
		{
			ft_putstr_fd("> ", 1);
			ret = get_next_line(0);
			if(!ret || ft_strncmp(ret, av, ft_strlen(ret) - 1) == 0)
				exit(0);
			write(p_fd[1], ret, ft_strlen(ret));
		}
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

char *my_getenv(char *name, char **env)
{
	int i = 0;

	while(env[i])
	{
		int j = 0;
		while(env[i][j] && env[i][j] != '=')
			j++;
		if(ft_strcmp(ft_substr(env[i], 0, j), name) == 0)
			return env[i] + j + 1;
		i++;
	}
	return NULL;
}

char *get_path(char *cmd, char **env)
{
	int 	i;
	char 	**args;
	char 	*exec;
	char 	**allpath;

	allpath = ft_split(my_getenv("PATH", env), ':');
	args = ft_split(cmd, ' ');
	i = -1;
	if (access(args[0], X_OK) == 0)
		return args[0];
	else
	{
		while (allpath[++i])
		{
			allpath[i] = ft_strjoin(allpath[i], "/");
			exec = ft_strjoin(allpath[i], args[0]);
			free(allpath[i]);
			if (access(exec, F_OK | X_OK) == 0)
				break ;
			free(exec);
		}
	}
	return exec;
}

void	pipex(t_pipex *tab, char *cmd)
{
	pid_t	pid;
	int p_fd[2];

	if(pipe(p_fd) == -1)
		perror("pipe");
	pid = fork();
	if(pid == -1)
		perror("fork");
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		execve(get_path(cmd, tab->env), ft_split(cmd, ' '), tab->env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*tab;
	int		i;
	
	if (ac >= 5)
	{
		tab = malloc(sizeof(t_pipex));
		tab->env = env;
		tab->av = av;
		if(ft_strcmp(av[1], "here_doc") == 0)
		{
			i = 3;
			tab->fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND , 0777);
			here_doc(av[2], tab);
		}
			
		else
		{
			i = 2;
			tab->fd1 = open(av[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			tab->fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(tab->fd1, 0);
		}
		while(i < ac - 2)
			pipex(tab, av[i++]);
		dup2(tab->fd2, 1);
		execve(get_path(av[ac - 2], env), ft_split(av[i], ' '), env);
	}
	else
		ft_putstr_fd("$RES_REAL: ambiguous redirect\n", 2);
}

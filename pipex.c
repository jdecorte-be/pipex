#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include <stdlib.h>
#include "libft/libft.h"

#include "pipex.h"


// void ft_parsing(char **env, char **argv)
// {
// 	char **envsplit;
// 	char **cmdac;

// 	envsplit = ft_split(env[4], ':');
// 	cmdac = ft_split(argv[2], ' ');

// }

void p_child(t_pipex *tab)
{
	dup2(tab->fd1, STDIN_FILENO);
	dup2(tab->p_fd[1], STDOUT_FILENO);
	close(tab->p_fd[0]);
	close(tab->fd1);
	// execve for each command
	exit(EXIT_FAILURE);
}

void p_parent(t_pipex *tab)
{
	int status;
	waitpid(-1, &status, 0);
	dup2(tab->fd2, STDOUT_FILENO);
	dup2(tab->p_fd[0], STDIN_FILENO);
	close(tab->p_fd[1]);
	close(tab->fd2);

	// execve for each command
	int i = -1;
	char *cmd;
	while(tab->s_env[++i])
	{
		cmd = ft_strjoin(tab->s_env[i], tab->av[2]);
		execve(cmd, tab->cmdac, tab->env);
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

void pipex(t_pipex *tab)
{
	int p_fd[2];
	pid_t pid;

	pipe(p_fd);
	tab->p_fd = p_fd;
	pid = fork();
	if (pid == 0)
		p_child(tab);
	else
		p_parent(tab);
}


int main(int ac, char *av[], char *env[])
{
	t_pipex *tab;
	int file1, file2;
	char **envsplit;
	char **cmdac;

	tab = malloc(sizeof(t_pipex));
	tab->fd1 = open(av[1], O_RDONLY);
	tab->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	tab->s_env = ft_split(env[4], ':');
	tab->cmdac = ft_split(av[2], ' ');
	tab->env = env;
	tab->av = av;

	pipex(tab);
	return 0;
}

//  ./a.out infile "ls -l" "wc -l" outfile
 
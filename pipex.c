#include "libft/libft.h"
#include "pipex.h"

void p_child1(t_pipex *tab)
{
	char	**cmd1;
	char	*cmd;
	int		i;
	char	*PATH_from_envp = ft_substr(tab->env[4], 58, 90);
	char	**allpaths = ft_split(PATH_from_envp, ':');

	cmd1 = ft_split(tab->av[2], ' ');
	dup2(tab->fd1, 0);
	dup2(tab->p_fd[1], 1);
	close(tab->p_fd[0]);
	close(tab->fd1);
	// execve for each commands
	int ret = 0;
	i = -1;
	while (allpaths[++i])
	{
		allpaths[i] = ft_strjoin(allpaths[i], "/");
		cmd = ft_strjoin(allpaths[i], cmd1[0]);
		ret = execve(cmd, &cmd1[0], tab->env);
		free(cmd);
	}
	if (ret < 0)
		exit(127);
	exit(EXIT_FAILURE);
}

void p_child2(t_pipex *tab)
{
	int		status;
	char	**cmd1 = ft_split(tab->av[3], ' ');
	char	*PATH_from_envp = ft_substr(tab->env[4], 58, 90);
	char	**allpaths = ft_split(PATH_from_envp, ':');

	waitpid(-1, &status, 0);
	dup2(tab->p_fd[0], 0);
	dup2(tab->fd2, 1);
	close(tab->p_fd[1]);
	close(tab->fd2);
	// execve for each command
	char *cmd;
	int ret = 0;
	int i = -1;
	while (allpaths[++i])
	{
		allpaths[i] = ft_strjoin(allpaths[i], "/");
		cmd = ft_strjoin(allpaths[i], cmd1[0]);
		execve(cmd, &cmd1[0], tab->env);
		free(cmd);
	}
	if (ret < 0)
		exit(127);
	exit(EXIT_FAILURE);
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
		tab->fd1 = open(av[1], O_RDONLY);
		tab->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (tab->fd1 < 0 || tab->fd2 < 0)
		{
			write(STDERR, "\e[0;31m[ERROR] File dont exist\n", 100);
			exit(1);
		}
		tab->env = env;
		tab->av = av;
		pipex(tab);
		close(file1);
		close(file2);
	}
	else
	{
		write(STDERR, "\e[0;31m[ERROR] Invalid number of arguments.\n Usage : ./pipex infile ''ls -l'' ''wc -l'' outfile\n", 100);
		exit(1);
	}

}

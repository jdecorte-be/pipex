#ifndef PIPEX_H
# define PIPEX_H

#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  

typedef struct s_pipex
{
	int     fd1;
    int     fd2;
    char    **av;
    char    **env;
    char    **s_env;
    char    **cmdac;
    int *p_fd;
}		t_pipex;

#endif // !PIPEX_H
#include "../pipex.h"

int main(int ac, char **av, char **env)
{
	execve("/bin/ls", &av[1], env);
}
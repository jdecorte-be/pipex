/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 18:41:50 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/31 18:42:07 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_tab(t_pipex *tab)
{
	int	j;

	tab->fd1 = open(tab->av[1], O_RDONLY);
	tab->fd2 = open(tab->av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
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

int	main(int ac, char *av[], char *env[])
{
	t_pipex	*tab;

	if (ac == 5)
	{
		tab = malloc(sizeof(t_pipex));
		tab->env = env;
		tab->av = av;
		init_tab(tab);
		pipex(tab);
		close(tab->fd1);
		close(tab->fd2);
	}
	else
		puterror("$RES_REAL: ambiguous redirect\n");
	exit(1);
}

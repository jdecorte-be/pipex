/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:19:27 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/02 11:25:07 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (((unsigned char)first[i] != (unsigned char)second[i]
				|| first[i] == 0) || second[i] == 0)
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i++;
	}
	return (0);
}

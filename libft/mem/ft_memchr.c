/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:18:07 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/01 12:18:07 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	unsigned char	*strtosrc;
	size_t			i;

	strtosrc = (unsigned char *)memoryBlock;
	i = 0;
	while (i < size)
	{
		if (*strtosrc == (unsigned char)searchedChar)
			return (strtosrc);
		strtosrc++;
		i++;
	}
	return (NULL);
}

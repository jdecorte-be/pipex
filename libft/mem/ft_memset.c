/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:18:16 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/01 17:24:23 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	char	*strptr;
	size_t	i;

	strptr = (char *)ptr;
	i = 0;
	while (i < count)
	{
		strptr[i] = value;
		i++;
	}
	return (ptr);
}

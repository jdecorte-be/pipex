/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:19:33 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/01 12:19:33 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr( const char *s, int searchedChar )
{
	int		i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	while (i >= 0)
	{	
		if (str[i] == (char)searchedChar)
			return (str + i);
		i--;
	}
	return (NULL);
}

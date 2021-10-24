/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 11:47:52 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/02 20:59:56 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			signe;
	long long	res;

	i = 0;
	signe = 1;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		res = (res * 10) + (str[i++] - 48);
		if (res * signe < -2147483648)
			return (0);
		if (res * signe > 2147483647)
			return (-1);
	}
	return (res * signe);
}

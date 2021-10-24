/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isintp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:59:53 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/19 17:02:23 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	isint(t_print *tab)
{
	int		res;
	char	*intmin;

	intmin = "-2147483648";
	res = va_arg(tab->args, long int);
	if (-2147483647 >= res)
		tab->len += 10;
	if (res < 0)
	{
		res = -res;
		tab->len ++;
		ft_putchar('-');
	}
	ft_putnbr(res);
	if (res == 0)
		tab->len++;
	while (res > 0)
	{
		res = res / 10;
		tab->len ++;
	}
}

void	isdecint(t_print *tab)
{
	int	res;

	res = va_arg(tab->args, int);
	ft_putbase10(res, tab);
}

void	isperc(t_print *tab)
{
	ft_putchar('%');
	tab->len++;
}

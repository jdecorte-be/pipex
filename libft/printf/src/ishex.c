/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ishex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:31:43 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/19 17:00:40 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ispointer(t_print *tab)
{
	unsigned long	res;

	res = va_arg(tab->args, unsigned long);
	ft_putstr("0x");
	tab->len += 2;
	ft_putpnt(res, tab);
}

void	ishexmin(t_print *tab)
{
	int	res;

	res = va_arg(tab->args, unsigned int);
	ft_puthexmin(res, tab);
}

void	ishexmaj(t_print *tab)
{
	int	res;

	res = va_arg(tab->args, unsigned int);
	ft_puthexmaj(res, tab);
}

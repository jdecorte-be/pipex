/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:28:11 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/19 15:31:27 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putbase10(unsigned int i, t_print *tab)
{
	char	*base;

	base = "0123456789";
	if (i >= 10)
	{
		ft_putbase10(i / 10, tab);
		ft_putbase10(i % 10, tab);
	}
	else
	{
		ft_putchar(base[i]);
		tab->len++;
	}
}

void	ft_puthexmin(unsigned int i, t_print *tab)
{
	char	*base;

	base = "0123456789abcdef";
	if (i >= 16)
	{
		ft_puthexmin(i / 16, tab);
		ft_puthexmin(i % 16, tab);
	}
	else
	{
		ft_putchar(base[i]);
		tab->len++;
	}
}

void	ft_puthexmaj(unsigned int i, t_print *tab)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (i >= 16)
	{
		ft_puthexmaj(i / 16, tab);
		ft_puthexmaj(i % 16, tab);
	}
	else
	{
		ft_putchar(base[i]);
		tab->len++;
	}
}

void	ft_putpnt(unsigned long int i, t_print *tab)
{
	char	*base;

	base = "0123456789abcdef";
	if (i >= 16)
	{
		ft_putpnt(i / 16, tab);
		ft_putpnt(i % 16, tab);
	}
	else
	{
		ft_putchar(base[i]);
		tab->len++;
	}
}

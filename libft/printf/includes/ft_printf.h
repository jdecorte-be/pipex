/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:27:30 by jdecorte          #+#    #+#             */
/*   Updated: 2021/10/19 17:04:28 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_print
{
	va_list	args;
	int		len;
}		t_print;

void	ft_putbase10(unsigned int i, t_print *tab);
void	ft_puthexmin(unsigned int i, t_print *tab);
void	ft_puthexmaj(unsigned int i, t_print *tab);
void	ft_putpnt(unsigned long int i, t_print *tab);

int		ft_printf(const char *input, ...);
void	ispointer(t_print *tab);
void	ishexmin(t_print *tab);
void	ishexmaj(t_print *tab);
void	ischar(t_print *tab);
void	isint(t_print *tab);

void	isstring(t_print *tab);
char	*ft_strchr(const char *string, int searchedChar);

void	ft_putchar(char c);
void	ft_putnbr(long int nb);
void	ft_putstr(char *str);
void	isdecint(t_print *tab);
void	isperc(t_print *tab);

size_t	ft_strlen(const char *theString);

#endif

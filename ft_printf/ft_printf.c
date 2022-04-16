/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:29:42 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/16 22:27:16 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_arg(const char perc_type, va_list args)
{
	if (perc_type == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (perc_type == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (perc_type == 'p')
		return (ft_putptr(va_arg(args, unsigned long long)));
	else if (perc_type == 'd' || perc_type == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (perc_type == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (perc_type == 'x')
		return (ft_putnbr_base(va_arg(args, int), "0123456789abcdef"));
	else if (perc_type == 'X')
		return (ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF"));
	else if (perc_type == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	size;

	va_start(args, str);
	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			size += ft_print_arg(str[i + 1], args);
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			size++;
		}
		i++;
	}
	va_end(args);
	return (size);
}

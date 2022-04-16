/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:55:58 by mpeharpr          #+#    #+#             */
/*   Updated: 2021/12/17 20:05:15 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Print a string to console */
size_t	ft_putstr(const char *str)
{
	size_t	len;

	if (!str)
		return (ft_putstr("(null)"));
	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}

/* Print a character to console */
size_t	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

/* Print an int to console */
size_t	ft_putnbr(int nb)
{
	long long int	final;
	int				neg;

	neg = 1;
	final = nb;
	if (final < 0)
	{
		final *= -1;
		neg *= -1;
		ft_putchar('-');
	}
	if (final > 9)
	{
		ft_putnbr((final / 10));
		ft_putchar((final % 10 + '0'));
	}
	else
		ft_putchar((final + '0'));
	return (ft_count_digits(final * neg, 10));
}

/* Print an unsigned int to console */
size_t	ft_putunbr(unsigned int nb)
{
	unsigned long long int	final;

	final = nb;
	if (final > 9)
	{
		ft_putnbr((final / 10));
		ft_putchar((final % 10 + '0'));
	}
	else
		ft_putchar((final + '0'));
	return (ft_count_digits(final, 10));
}

/* Print the address of a pointer to the console */
size_t	ft_putptr(unsigned long long ptr)
{
	char				*hexabase;
	char				*final;
	size_t				i;
	size_t				size;

	hexabase = "0123456789abcdef";
	i = ft_count_udigits(ptr, 16);
	final = malloc((i + 1) * sizeof(char));
	if (!final)
		return (0);
	ft_bzero(final, i + 1);
	i--;
	while ((ptr / 16) > 0 && i > 0)
	{
		final[i] = hexabase[(ptr % 16)];
		ptr /= 16;
		i--;
	}
	final[i] = hexabase[(ptr % 16)];
	size = ft_putstr("0x");
	size += ft_putstr(final);
	free(final);
	if (size == 2)
		size += ft_putchar('0');
	return (size);
}

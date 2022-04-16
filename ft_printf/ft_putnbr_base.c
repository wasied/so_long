/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:49 by mpeharpr          #+#    #+#             */
/*   Updated: 2021/12/17 20:35:27 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Check if the base is valid and can be used */
static int	ft_check_valid(const char *base)
{
	int	i;
	int	j;

	if (!base)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (i);
}

/* Recursively used to print a number in a specific base */
static size_t	ft_print(unsigned int nb, const char *base, size_t len)
{
	size_t	size;

	size = 0;
	if (nb >= len)
		size += ft_print(nb / len, base, len);
	size += ft_putchar(base[nb % len]);
	return (size);
}

/* Print a number in a specific base */
size_t	ft_putnbr_base(unsigned int nb, char *base)
{
	size_t	len;
	size_t	size;

	len = ft_check_valid(base);
	if (!len)
		return (0);
	size = ft_print(nb, base, len);
	return (size);
}

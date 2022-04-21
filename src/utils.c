/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:30 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/21 20:24:03 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Dynamically allocate a string and put a '\0' at the end of it
@param str -> The string that will be allocated
@return char* -> The allocated string
*/
char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	str_len;
	char	*ptr;

	str_len = ft_strlen((char *)str);
	ptr = malloc((str_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/* Compare 2 strings in order to know if they are identical
@param s1 -> First string
@param s2 -> Second string
@return int -> The ASCII difference between both
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

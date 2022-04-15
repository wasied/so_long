/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:25 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/16 00:55:11 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Get the minimum value between 2 values
@param uno -> The first value
@param dos -> The second value
@return int: the minimum value
*/
int	get_min(int uno, int dos)
{
	if (uno > dos)
		return (uno);
	return (dos);
}

/* Get the maximum value between 2 values
@param uno -> The first value
@param dos -> The second value
@return int: the maximum value
*/
int	get_max(int uno, int dos)
{
	if (uno < dos)
		return (uno);
	return (dos);
}

/* Clamp value between min and max
@param value -> The value to clamp
@param min -> The minimum value
@param max -> The maximum value
@return int: the clamped value
*/
int	clamp(int value, int min, int max)
{	
	return (get_max(get_min(value, min), max));
}

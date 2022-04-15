/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:21 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/16 01:40:53 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Called when a player is on a pickup item (=> burger or exit)
@param vars -> pointing to the t_game structure
@return int:
	0 = do not use the default overwriting image
	1 = use the default overwriting image
*/
int	pickup_item(t_game *vars, int itemid)
{
	if (itemid == 2)
	{
		vars->pickups++;
		printf("You picked up a burger !\n");
	}
	else if (itemid == 3)
	{
		if (vars->pickups < vars->s_map->burgers)
		{
			printf("You haven't picked up all the burgers yet!\n");
			return (0);
		}
		else
		{
			printf("\nYou won the game with %zu moves!\n", vars->moves);
			printf("You picked up %zu burgers.\n", vars->pickups);
			free_map(vars->s_map, "Relaunch the program to start a new game!");
		}
	}
	return (1);
}

/* Called to check if a player can go to the specific position
@param vars -> pointing to the t_game structure
@param x -> x-coord of the new pos to check
@param y -> y-coord of the new pos to check
@return int:
	0 = the slot is not available
	1 = the slot is empty
	2 = the slot is a burger
	3 = the slot is an exit
*/
int	can_player_go(t_game *vars, size_t x, size_t y)
{
	char	c;

	if (!vars->s_map->map[y])
		return (0);
	c = vars->s_map->map[y][x];
	if (!c)
		return (0);
	else if (c == '0' || c == 'P')
		return (1);
	else if (c == 'C')
		return (2);
	else if (c == 'E')
		return (3);
	return (0);
}

/* Called when a player moves in a direction 
@param direction -> 0 (left), 1 (up), 2 (right), 3 (bottom)
*/
void	player_move(t_game *d, int direction)
{
	t_img	*ply;
	size_t	bx;
	size_t	by;
	int		i;
	int		overwrite;

	ply = d->ply_img;
	bx = ply->x;
	by = ply->y;
	if (direction == 0)
		ply->x = clamp(ply->x - 50, 50, (d->s_map->w - 2) * 50);
	else if (direction == 1)
		ply->y = clamp(ply->y - 50, 50, (d->s_map->h - 2) * 50);
	else if (direction == 2)
		ply->x = clamp(ply->x + 50, 50, (d->s_map->w - 2) * 50);
	else if (direction == 3)
		ply->y = clamp(ply->y + 50, 50, (d->s_map->h - 2) * 50);
	i = can_player_go(d, ply->x / 50, ply->y / 50);
	if (i == 0)
	{
		ply->x = bx;
		ply->y = by;
		return ;
	}
	d->moves++;
	printf("Total amount of moves: %zu\n", d->moves);
	overwrite = 1;
	if (i == 2 || i == 3)
		overwrite = pickup_item(d, i);
	d->mlxdat->color = d->s_map->s_img->color;
	d->mlxdat->w = ply->w;
	d->mlxdat->h = ply->h;
	if (i != 1 && overwrite == 1)
	{	
		draw_rect(*d->mlxdat, ply->x, ply->y);
		d->s_map->map[ply->y / 50][ply->x / 50] = '0';
	}
	if (d->s_map->map[by / 50][bx / 50] == 'E')
	{
		draw_rect(*d->mlxdat, bx, by);
		draw_mat(*d->mlxdat, bx, by, "./assets/hospital.xpm");
	}
	else
		draw_rect(*d->mlxdat, bx, by);
	*d->ply_img = draw_mat(*d->mlxdat, ply->x, ply->y, "./assets/fat.xpm");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:21 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/17 04:19:33 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Called when a player is on a pickup item (=> burger or exit)
@param vars -> pointing to the t_game structure
@return int:
	0 = do not use the default overwriting image
	1 = use the default overwriting image
	2 = stop everything
*/
int	pickup_item(t_game *vars, int itemid)
{
	if (itemid == 2)
	{
		vars->pickups++;
		ft_printf("You picked up a burger !\n");
	}
	else if (itemid == 3)
	{
		if (vars->pickups < vars->s_map->burgers)
		{
			ft_printf("You haven't picked up all the burgers yet!\n");
			return (0);
		}
		else
		{
			ft_printf("\nYou won the game with %u moves!\n", vars->moves);
			ft_printf("You picked up %u burgers.\n", vars->pickups);
			stop_game(vars);
			return (2);
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

/* Called after player has made a move (norminette :()
@param d -> pointing to the t_game structure
@param i -> the value that can_player_go returned
@param x -> x-coord of the old player pos
@param y -> y-coord of the old player pos
*/
void	after_move(t_game *d, int i, size_t bx, size_t by)
{
	t_img	*ply;
	size_t	overwrite;

	ft_printf("Total amount of moves: %u\n", d->moves);
	ply = d->ply_img;
	overwrite = 1;
	if (i == 2 || i == 3)
		overwrite = pickup_item(d, i);
	if (overwrite == 2)
		return ;
	d->mlx->color = d->s_map->s_img->color;
	d->mlx->w = ply->w;
	d->mlx->h = ply->h;
	if (i != 1 && overwrite == 1)
	{	
		rep(d, d->bg, drect(*d->mlx, ply->x, ply->y).img);
		d->s_map->map[ply->y / 50][ply->x / 50] = '0';
	}
	rep(d, d->bg, drect(*d->mlx, bx, by).img);
	if (d->s_map->map[by / 50][bx / 50] == 'E')
		rep(d, d->ex, dmat(*d->mlx, bx, by, "./assets/ex.xpm").img);
	rep(d, d->ply_img, dmat(*d->mlx, ply->x, ply->y, "./assets/ply.xpm").img);
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
	after_move(d, i, bx, by);
}

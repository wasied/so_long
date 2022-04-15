/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:27 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/16 01:10:48 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* A function to properly stop the game 
@param vars -> pointing to the t_game structure
*/
int	stop_game(t_game *vars)
{
	free_map(vars->s_map, "Thanks for playing The Burger King!");
	mlx_destroy_window(vars->mlxdat->mlxp, vars->mlxdat->winp);
	return (0);
}

/* Hook called when a button is pressed 
@param keycode -> The keycode the user pressed
@param vars -> pointing to the t_game structure
*/
int	button_pressed(int keycode, t_game *vars)
{
	if (keycode == 6)
		player_move(vars, 1);
	else if (keycode == 1)
		player_move(vars, 3);
	else if (keycode == 0)
		player_move(vars, 0);
	else if (keycode == 2)
		player_move(vars, 2);
	else if (keycode == 53)
		stop_game(vars);
	return (0);
}

/* Get the position of a character in the map 
@param vars -> pointing to the t_game structure
@param search -> the character to search
@param x_ptr -> pointing to a size_t var that will be set to the X position
@param y_ptr -> pointing to a size_t var that will be set to the Y position
*/
void	get_item_pos(t_game *vars, char search, size_t *x_ptr, size_t *y_ptr)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < vars->s_map->h)
	{
		x = 0;
		while (x < vars->s_map->w)
		{
			if (vars->s_map->map[y][x] == search)
			{
				*x_ptr = x;
				*y_ptr = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

/* Generate burgers, walls & exits 
@param g -> pointing to the t_game structure
*/
void	generate_items(t_game *g)
{
	size_t	x;
	size_t	y;
	char	c;

	get_item_pos(g, 'P', &x, &y);
	*g->s_img_ply = draw_mat(*g->mlxdat, x * 50, y * 50, "./assets/fat.xpm");
	get_item_pos(g, 'E', &x, &y);
	draw_mat(*g->mlxdat, x * 50, y * 50, "./assets/hospital.xpm");
	y = 0;
	while (y < g->s_map->h)
	{
		x = 0;
		while (x < g->s_map->w)
		{
			c = g->s_map->map[y][x];
			if (c == '1')
				draw_mat(*g->mlxdat, x * 50, y * 50, "./assets/cucumber.xpm");
			else if (c == 'C')
				draw_mat(*g->mlxdat, x * 50, y * 50, "./assets/burger.xpm");
			x++;
		}
		y++;
	}
}

/* The main function */
int	main(void)
{
	t_mlx_data		d;
	t_map			map;
	t_img			player;
	t_img			background;
	t_game			stream;

	parse_map(&map, "test.ber");
	if (!map.map)
	{
		printf("Map is somehow invalid!");
		return (0);
	}
	d.mlxp = mlx_init();
	d.winp = mlx_new_window(d.mlxp, map.w * 50, map.h * 50, "Burger King");
	background = draw_rect(d, 0, 0, map.w * 50, map.h * 50, 0x003498db);
	map.s_img = &background;
	stream.mlxdat = &d;
	stream.s_map = &map;
	stream.s_img_ply = &player;
	stream.pickups = 0;
	stream.moves = 0;
	generate_items(&stream);
	mlx_hook(d.winp, 2, 1, button_pressed, &stream);
	mlx_hook(d.winp, 17, 1, stop_game, &stream);
	mlx_loop(d.mlxp);
	return (0);
}

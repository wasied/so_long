/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:10:03 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/17 04:26:05 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Called to check that all characters on the map are valids */
int	all_characters_valid(t_map *map)
{
	size_t	y;
	size_t	x;
	char	c;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			c = map->map[y][x];
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

/* Called to initialize the game (norminette :()
@param d -> t_mlx_data structure
@param map -> t_map structure
@param bg -> t_img structure background
@param game -> t_game structure
*/
void	initialize_game(t_mlx_data *d, t_map *map, t_img *bg, t_game *game)
{
	d->color = 0x003498db;
	d->w = map->w * 50;
	d->h = map->h * 50;
	*bg = drect(*d, 0, 0);
	game->wl = NULL;
	game->ex = NULL;
	game->br = NULL;
	game->bg = bg->img;
	map->s_img = bg;
	game->mlx = d;
	game->s_map = map;
	game->pickups = 0;
	game->moves = 0;
}

/* Called to initialize the map structure (norminette :()
@param map -> t_map structure
@param width -> size_t pointer to map width
@param tall -> size_t pointer to map tall
@param y -> size_t pointer to y
*/
void	initialize_map(t_map *map, size_t *width, size_t *tall, size_t *y)
{
	map->map[*y] = NULL;
	map->w = *width;
	map->h = *tall;
	if (all_characters_valid(map) == 0)
	{
		free_map(map, "The map is containing an invalid character!", 1);
		return ;
	}
	if (check_walls(map) == 0)
	{
		free_map(map, "Map must be surrounded by walls only!", 1);
		return ;
	}
	map->burgers = count_items(map, 'C');
	if (map->burgers <= 0)
		free_map(map, "Map need at least 1 burger!", 1);
	if (count_items(map, 'E') <= 0)
		free_map(map, "Map need at least 1 exit!", 1);
	if (count_items(map, 'P') <= 0)
		free_map(map, "Map need at least 1 start pos!", 1);
}

/* Callback called in a loop in map.c (norminette :()
@param map -> t_map structure
@param fd -> file descriptor integer
@param width -> size_t pointer to map width
@param y -> size_t pointer to y
*/
int	loop_map_initialize(t_map *map, int fd, size_t *width, size_t *y)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!*width)
		*width = ft_strlen(line);
	if (*width != ft_strlen(line) || *width < 3)
	{
		free_map(map, "Map must be a rectangle!", 1);
		return (1);
	}
	map->map[*y] = ft_strdup(line);
	if (!map->map[*y])
	{
		free_map(map, "A memory error has occured!", 1);
		return (1);
	}
	(*y)++;
	return (0);
}

/* Callback called in a loop in main.c (fuck norminette omfg)
@param g -> t_game structure
@param c -> the character passed to the loop
@param x -> size_t pointer describing the x position
@param y -> size_t pointer describing the y position
*/
void	place_right_item(t_game *g, char c, size_t x, size_t y)
{
	if (c == '1')
		rep(g, g->wl, dmat(*g->mlx, x * 50, y * 50, "./assets/wl.xpm").img);
	else if (c == 'C')
		rep(g, g->br, dmat(*g->mlx, x * 50, y * 50, "./assets/br.xpm").img);
	else if (c == 'E')
		rep(g, g->ex, dmat(*g->mlx, x * 50, y * 50, "./assets/ex.xpm").img);
}

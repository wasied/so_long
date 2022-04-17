/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 02:10:03 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/17 04:00:35 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	*bg = draw_rect(*d, 0, 0);
	game->walls_imgptr = NULL;
	game->exit_imgptr = NULL;
	game->burger_imgptr = NULL;
	game->bg_imgptr = bg->image;
	map->s_img = bg;
	game->mlxdat = d;
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

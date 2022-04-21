/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:17 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/21 20:20:28 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* C Libraries */
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

/* Our libraries */
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"

/* Our structures */

typedef struct s_mlx_data {
	void			*mlxp;
	void			*winp;
	unsigned int	color;
	size_t			w;
	size_t			h;
}	t_mlx_data;

typedef struct s_img {
	void			*img;
	char			*data;
	int				bpp;
	int				l_len;
	int				endian;
	unsigned int	color;
	size_t			x;
	size_t			y;
	size_t			w;
	size_t			h;
}	t_img;

typedef struct s_map {
	char			**map;
	t_img			*s_img;
	size_t			w;
	size_t			h;
	size_t			burgers;
}	t_map;

typedef struct s_game {
	t_img		*ply_img;
	t_map		*s_map;
	t_mlx_data	*mlx;
	size_t		pickups;
	size_t		moves;
	void		*bg;
	void		*wl;
	void		*ex;
	void		*br;
}	t_game;

/* Our prototypes */

/*** main.c ***/
int		stop_game(t_game *vars);
void	get_item_pos(t_game *vars, char search, size_t *x_ptr, size_t *y_ptr);
void	generate_items(t_game *vars);

/*** surface.c ***/
void	rep(t_game *d, void *already_init, void *new_img);
t_img	drect(t_mlx_data d, size_t x, size_t y);
t_img	dmat(t_mlx_data d, size_t x, size_t y, char *path);

/*** map.c ***/
void	parse_map(t_map *map, const char *path);
void	free_map(t_map *map, char *message, int error);
int		check_walls(t_map *map);
int		count_items(t_map *map, char c);

/*** utils.c ***/
char	*ft_strdup(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

/*** player.c ***/
int		can_player_go(t_game *vars, size_t x, size_t y);
void	player_move(t_game *vars, int direction);
int		can_player_go(t_game *vars, size_t x, size_t y);

/*** extra.c ***/
void	initialize_game(t_mlx_data *d, t_map *map, t_img *bg, t_game *game);
void	initialize_map(t_map *map, size_t *width, size_t *tall, size_t *y);
int		loop_map_initialize(t_map *map, int fd, size_t *width, size_t *y);
void	place_right_item(t_game *g, char c, size_t x, size_t y);

#endif
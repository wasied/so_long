/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:17 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/16 01:13:47 by mpeharpr         ###   ########.fr       */
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

/* Our libraries */
# include "mlx.h"
# include "../get_next_line/get_next_line.h"

/* Our structures */
typedef struct s_mlx_data {
	void	*mlxp;
	void	*winp;
}	t_mlx_data;

typedef struct s_img {
	void			*image;
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
	t_img		*s_img_ply;
	t_map		*s_map;
	t_mlx_data	*mlxdat;
	size_t		pickups;
	size_t		moves;
}	t_game;

typedef unsigned int	t_ui; /* norminette :( */

/* Our prototypes */

/*** main.c ***/
int		stop_game(t_game *vars);
void	get_item_pos(t_game *vars, char search, size_t *x_ptr, size_t *y_ptr);
void	generate_items(t_game *vars);

/*** surface.c ***/
t_img	draw_rect(t_mlx_data d, size_t x, size_t y, size_t w, size_t h, t_ui c);
t_img	draw_mat(t_mlx_data d, size_t x, size_t y, char *path);

/*** map.c ***/
void	parse_map(t_map *map, const char *path);
void	free_map(t_map *map, char *message);

/*** utils.c ***/
char	*ft_strdup(const char *str);

/*** player.c ***/
int		can_player_go(t_game *vars, size_t x, size_t y);
void	player_move(t_game *vars, int direction);
int		can_player_go(t_game *vars, size_t x, size_t y);

/*** math.c ***/
int		get_min(int uno, int dos);
int		get_min(int uno, int dos);
int		clamp(int value, int min, int max);

#endif
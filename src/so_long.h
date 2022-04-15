#ifndef SO_LONG_H
# define SO_LONG_H

/* C Libraries */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Our libraries */
#include "mlx.h"
#include "../get_next_line/get_next_line.h"

/* Our structures */
typedef struct s_mlx_data {
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx_data;

typedef struct s_img {
	void			*image;
	char			*data;
	int				bpp;
	int				line_len;
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
	t_mlx_data	*s_mlx_data;
	size_t		pickups;
	size_t		moves;
}	t_game;

/* Our prototypes */

/*** main.c ***/
int		stop_game(t_game *vars);
void	get_item_pos(t_game *vars, char search, size_t *x_ptr, size_t *y_ptr);
void	generate_items(t_game *vars);

/*** surface.c ***/
t_img	draw_rect(t_mlx_data data, size_t x, size_t y, size_t w, size_t h, unsigned int color);
t_img	draw_texture(t_mlx_data data, size_t x, size_t y, char *path);

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
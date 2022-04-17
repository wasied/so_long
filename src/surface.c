/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:54:29 by mpeharpr          #+#    #+#             */
/*   Updated: 2022/04/17 04:06:07 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Properly clear an image pointer and set a new image to the pointer
@param d -> t_game structure
@param already_init -> pointer to where the image is stored on our structs
@param new_img -> pointer of the new image that has been created
*/
void	replace_img(t_game *d, void *already_init, void *new_img)
{
	if (already_init == NULL)
		already_init = new_img;
	else
	{
		mlx_destroy_image(d->mlxdat->mlxp, new_img);
		new_img = already_init;
	}
}

/* Initialize the rectangle structure
@param data -> t_mlx_data structure
@param im -> t_img structure
@param x -> the X position of the upper-left pixel of the rectangle
@param y -> the Y position of the upper-left pixel of the rectangle
*/
void	initialize_rect(t_mlx_data *d, t_img *im, size_t x, size_t y)
{
	im->x = x;
	im->y = y;
	im->w = d->w;
	im->h = d->h;
	im->image = mlx_new_image(d->mlxp, d->w, d->h);
	im->data = mlx_get_data_addr(im->image, &im->bpp, &im->l_len, &im->endian);
	im->color = mlx_get_color_value(d->mlxp, d->color);
}

/* Draw a rectangle with a specific image
@param data -> t_mlx_data structure
@param x -> the X position of the upper-left pixel of the rectangle
@param y -> the Y position of the upper-left pixel of the rectangle
@return t_img -> the rectangle structure that has been generated
*/
t_img	draw_rect(t_mlx_data d, size_t x, size_t y)
{
	t_img	img;
	size_t	pos_y;
	size_t	pos_x;
	size_t	pixel;

	initialize_rect(&d, &img, x, y);
	pos_y = 0;
	while (pos_y < d.h)
	{
		pos_x = 0;
		while (pos_x < d.w)
		{
			pixel = (pos_y * img.l_len) + (pos_x * 4);
			img.data[pixel] = img.color;
			img.data[pixel + 1] = img.color >> 8;
			img.data[pixel + 2] = img.color >> 16;
			img.data[pixel + 3] = img.color >> 24;
			pos_x++;
		}
		pos_y++;
	}
	mlx_put_image_to_window(d.mlxp, d.winp, img.image, x, y);
	return (img);
}

/* Draw a texture
@param data -> t_mlx_data structure
@param x -> the X position of the upper-left pixel of the texture
@param y -> the Y position of the upper-left pixel of the texture
@param path -> the relative path of the texture
@return t_img -> the rectangle structure that has been generated
*/
t_img	draw_mat(t_mlx_data data, size_t x, size_t y, char *path)
{
	t_img	mat;
	int		w;

	w = 0;
	mat.image = mlx_xpm_file_to_image(data.mlxp, path, &w, &w);
	mat.data = mlx_get_data_addr(mat.image, &mat.bpp, &mat.l_len, &mat.endian);
	mlx_put_image_to_window(data.mlxp, data.winp, mat.image, x, y);
	mat.x = x;
	mat.y = y;
	mat.w = w;
	mat.h = w;
	return (mat);
}

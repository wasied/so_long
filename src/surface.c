#include "so_long.h"

/* Draw a rectangle with a specific image
@param data -> t_mlx_data structure
@param x -> the X position of the upper-left pixel of the rectangle
@param y -> the Y position of the upper-left pixel of the rectangle
@param w -> the width of the rectangle
@param h -> the height of the rectangle
@param color -> the value of color
@return t_img -> the rectangle structure that has been generated
*/
t_img	draw_rect(t_mlx_data data, size_t x, size_t y, size_t w, size_t h, unsigned int color)
{
	t_img	img;

	img.x = x;
	img.y = y;
	img.w = w;
	img.h = h;
	img.image = mlx_new_image(data.mlx_ptr, w, h);
	img.data = mlx_get_data_addr(img.image, &img.bpp, &img.line_len, &img.endian);
	img.color = mlx_get_color_value(data.mlx_ptr, color);
	for (size_t pos_y = 0; pos_y < h; ++pos_y) {
		for (size_t pos_x = 0; pos_x < w; ++pos_x) {
			size_t pixel = (pos_y * img.line_len) + (pos_x * 4);

			img.data[pixel] = img.color;
			img.data[pixel + 1] = img.color >> 8;
			img.data[pixel + 2] = img.color >> 16;
			img.data[pixel + 3] = img.color >> 24;
		}
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img.image, x, y);
	return (img);
}

/* Draw a texture
@param data -> t_mlx_data structure
@param x -> the X position of the upper-left pixel of the texture
@param y -> the Y position of the upper-left pixel of the texture
@param path -> the relative path of the texture
@return t_img -> the rectangle structure that has been generated
*/
t_img	draw_texture(t_mlx_data data, size_t x, size_t y, char *path)
{
	t_img	texture;
	int		w;

	w = 0;
	texture.image = mlx_xpm_file_to_image(data.mlx_ptr, path, &w, &w);
	texture.data = mlx_get_data_addr(texture.image, &texture.bpp, &texture.line_len, &texture.endian);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, texture.image, x, y);
	texture.x = x;
	texture.y = y;
	texture.w = w;
	texture.h = w;
	return (texture);
}
#include "cub3D.h"

void	drawfloorceiling(t_img *img)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y <= WIN_H / 2)
	{
		while (++x <=WIN_W)
			put_pixel_img(img, x, y, 0x00333333);
		x = -1;
	}
	while (++y <= WIN_H)
	{
		while (++x <=WIN_W)
			put_pixel_img(img, x, y, 0x00954242);
		x = -1;
	}
}

void	draw3d(t_img *img, double dist, int x, int orientation) //need to explain name for rad_ang, why not current_angle or something else ?
{
	float	wall_bot;
	float	wall_top;
	float	line_height;

	line_height = (WIN_H / dist);
	wall_top = -line_height / 2 + WIN_H / 2;
	if (wall_top < 0)
		wall_top = 0;
	wall_bot = line_height / 2 + WIN_H / 2;
	if (wall_bot >= WIN_H)
		wall_bot = WIN_H - 1;
	while (--wall_bot > wall_top)
		put_pixel_img(img, x, (int)wall_bot, orientation);
}

void	init_texture(t_data *data)
{
	data->textures[0].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[0], &data->textures[0].h, &data->textures[0].w);
	data->textures[1].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[1], &data->textures[1].h, &data->textures[1].w);
	data->textures[2].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[2], &data->textures[2].h, &data->textures[2].w);
	data->textures[3].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[3], &data->textures[3].h, &data->textures[3].w);
}

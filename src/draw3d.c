#include "cub3D.h"

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

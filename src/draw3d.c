#include "cub3D.h"

void	draw3d(t_img *img, double dist, double rad_ang) //need to explain name for rad_ang, why not current_angle or something else ?
{
	double	wall_bot = 1 / dist * (WIN_H + WIN_H / 2);
	double	wall_top = 1 / dist * (WIN_H - WIN_H / 2);

	while (--wall_bot > wall_top)
		put_pixel_img(img, rad_ang, (int)wall_bot, 0x00FFFFFF);
	(void)rad_ang;
}

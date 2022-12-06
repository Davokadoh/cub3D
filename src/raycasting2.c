/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/06 17:55:13 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

t_cam	init_ray(t_cam player, double radius_angle)
{
	t_cam	ray;

	ray.angle = player.angle + radius_angle;
	ray.pos.x = player.pos.x;
	ray.pos.y = player.pos.y;
	ray.dir.x = cos(ray.angle);
	ray.dir.y = sin(ray.angle);
	printf("ray.angle %f,ray.pos.x%f, ray.pos.y%f, ray.dir.x%f, ray.dir.y%f \n", ray.angle, ray.pos.x,ray.pos.y, ray.dir.x, ray.dir.y );
	return (ray);
}

int	check_wall(char **map, t_cam *ray, int ray_dir)
{
	float	dist_h;
	float	dist_v;
	int		abs_x;
	int		abs_y;

	abs_x = (int)(fabs(ray->pos.y));
	abs_y = (int)(fabs(ray->pos.x));
	dist_h = dist_next_h(*ray, ray_dir);
	dist_v = dist_next_v(*ray, ray_dir);
	printf("dist_h %f, dist_v%f\n",dist_h, dist_v );
	if (dist_h <= dist_v)
		return (update_rayh(map, ray, ray_dir, dist_h));
	else
		return (update_rayv(map, ray, ray_dir, dist_v));

}

float	ray_dist(char **map, t_cam const player, t_cam *ray)
{
	float	dist;

	while (check_wall(map, ray, ray_dir(*ray)) != 1)
		;
	dist = sqrt(pow(fabs(player.pos.x - ray->pos.x), 2)
			+ pow(fabs(player.pos.y - ray->pos.y), 2));
	return (dist);
}

void	view_field(t_data *data, double rad_tot)
{
	double	rad_ang;
	t_img	p_view2d;
	t_img	p_view3d;
	float	dist;
	t_cam	ray;

	p_view2d.img = mlx_new_image(data->mlx, MM_W, MM_H);
	p_view2d.addr = mlx_get_data_addr(p_view2d.img, &p_view2d.bits_per_pixel,
			&p_view2d.line_size, &p_view2d.endian);
	init_img(&p_view2d, MM_W, MM_H);
	p_view3d.img = mlx_new_image(data->mlx, data->map_w, data->map_h);
	p_view3d.addr = mlx_get_data_addr(p_view3d.img, &p_view3d.bits_per_pixel,
			&p_view3d.line_size, &p_view3d.endian);
	rad_ang = -rad_tot / 2;
	// while (rad_ang <= rad_tot / 2)
	// {
		ray = init_ray(data->player, rad_ang);
		dist = ray_dist(data->map, data->player, &ray);
		// draw3d(dist, data->player, rad_ang, p_view3d);
		printf("player x%f Y%f, ray x%f y%f\n", data->player.pos.x, data->player.pos.y, ray.pos.x, ray.pos.y );
		put_pixel_img(&p_view2d, data->player.pos.x * wall_size(data) + wall_size(data)/2, data->player.pos.y * wall_size(data) + wall_size(data)/2, 0x00000000);
		draw_line(&p_view2d, data->player.pos, ray.pos, 0x00000000, data);
		rad_ang += DR;
	// }
	// mlx_put_image_to_window(data->mlx, data->win, p_view3d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, p_view2d.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/07 15:06:14 by jleroux          ###   ########.fr       */
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
	return (ray);
}

int	check_wall(char **map, t_cam *ray, int ray_dir)
{
	float	dist_h;
	float	dist_v;

	dist_h = dist_next_h(*ray, ray_dir);
	dist_v = dist_next_v(*ray, ray_dir);
	//printf("ray->pos.x %f, ray->pos.y %f\n", ray->pos.x, ray->pos.y);
	//printf("dist_h %f, dist_v%f\n",dist_h, dist_v );
	if (dist_v <= dist_h)
		return (update_rayv(map, ray, ray_dir, dist_v));
	else
		return (update_rayh(map, ray, ray_dir, dist_h));
}

float	ray_dist(char **map, t_cam const player, t_cam *ray)
{
	float	dist;
	int		dir_ray;
	int		i = 5;

	dir_ray = ray_dir(*ray);
	while (check_wall(map, ray, dir_ray) != 1 && --i > 0)
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
	// float	dist;
	t_cam	ray;

	p_view2d.img = mlx_new_image(data->mlx, MM_W, MM_H);
	p_view2d.addr = mlx_get_data_addr(p_view2d.img, &p_view2d.bits_per_pixel,
			&p_view2d.line_size, &p_view2d.endian);
	init_img(&p_view2d, MM_W, MM_H);
	p_view3d.img = mlx_new_image(data->mlx, data->map_w, data->map_h);
	p_view3d.addr = mlx_get_data_addr(p_view3d.img, &p_view3d.bits_per_pixel,
			&p_view3d.line_size, &p_view3d.endian);
	rad_ang = -rad_tot / 2;
	while (rad_ang <= rad_tot / 2)
	{
		ray = init_ray(data->player, rad_ang);
		ray_dist(data->map, data->player, &ray);
		// draw3d(dist, data->player, rad_ang, p_view3d);
		draw_line(&p_view2d, data->player.pos, ray.pos, 0x00000000, data);
		rad_ang += DR/2;
	}
	 mlx_put_image_to_window(data->mlx, data->win, p_view3d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, p_view2d.img, 0, 0);
}

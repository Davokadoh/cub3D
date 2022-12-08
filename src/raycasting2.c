/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/08 11:12:46 by vhaefeli         ###   ########.fr       */
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
	double	dist_h;
	double	dist_v;

	dist_h = dist_next_h(*ray, ray_dir);
	dist_v = dist_next_v(*ray, ray_dir);
	if (dist_v <= dist_h)
		return (update_rayv(map, ray, ray_dir, dist_v));
	else
		return (update_rayh(map, ray, ray_dir, dist_h));
}

double	ray_dist(char **map, t_cam const player, t_cam *ray)
{
	double	dist;
	int		dir_ray;
	int		i = 10;

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
	// t_img	data->view2d;
	// t_img	data->view3d;
	// double	dist;
	t_cam	ray;

	data->view2d.img = mlx_new_image(data->mlx, MM_W, MM_H);
	data->view2d.addr = mlx_get_data_addr(data->view2d.img, &data->view2d.bits_per_pixel,
			&data->view2d.line_size, &data->view2d.endian);
	init_img(&data->view2d, MM_W, MM_H);
	data->view3d.img = mlx_new_image(data->mlx, data->map_w, data->map_h);
	data->view3d.addr = mlx_get_data_addr(data->view3d.img, &data->view3d.bits_per_pixel,
			&data->view3d.line_size, &data->view3d.endian);
	rad_ang = -rad_tot / 2;
	while (rad_ang <= rad_tot / 2)
	{
		ray = init_ray(data->player, rad_ang);
		ray_dist(data->map, data->player, &ray);
		// draw3d(dist, data->player, rad_ang, data->view3d);
		draw_line(&data->view2d, data->player.pos, ray.pos, 0x00000000, data);
		rad_ang += DR / 20;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->view3d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->view2d.img, 0, 0);
}

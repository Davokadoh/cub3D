/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/10 18:52:14 by vhaefeli         ###   ########.fr       */
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
	{
		ray->c = 1;
		return (update_rayv(map, ray, ray_dir, dist_v));
	}
	else
	{
		ray->c = 2;
		return (update_rayh(map, ray, ray_dir, dist_h));
	}
}

double	ray_dist(char **map, t_cam const player, t_cam *ray, double rad_ang)
{
	double	dist;
	int		dir_ray;

	dir_ray = ray_dir(*ray);
	while (check_wall(map, ray, dir_ray) != 1)
		;
	dist = sqrt(pow(fabs(player.pos.x - ray->pos.x), 2)
			+ pow(fabs(player.pos.y - ray->pos.y), 2));
	dist = cos(rad_ang) * dist;
	return (dist);
}

int	compass(t_cam ray)
{
	int		dir_ray;

	dir_ray = ray_dir(ray);
	if ((dir_ray == 3 || dir_ray == 4) && ray.c == 2)
		return (0x00FFFF90);
	else if ((dir_ray == 1 || dir_ray == 4) && ray.c == 1)
		return (0x00FF90FF);
	else if ((dir_ray == 1 || dir_ray == 2) && ray.c == 2)
		return (0x0090FFFF);
	else if ((dir_ray == 2 || dir_ray == 3) && ray.c == 1)
		return (0x00FF0000);
	printf("cas non determine\n");
	return (0x00000000);
}

void	view_field(t_data *data, double rad_tot)
{
	double	rad_ang;
	double	dist;
	t_cam	ray;
	int		orientation;

	data->view2d.img = mlx_new_image(data->mlx, MM_W, MM_H);
	data->view2d.addr = mlx_get_data_addr(data->view2d.img, &data->view2d.bits_per_pixel,
			&data->view2d.line_size, &data->view2d.endian);
	init_img(&data->view2d, MM_W, MM_H);
	data->view3d.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->view3d.addr = mlx_get_data_addr(data->view3d.img, &data->view3d.bits_per_pixel,
			&data->view3d.line_size, &data->view3d.endian);
	rad_ang = -rad_tot / 2;
	int x = -1;
	//while (rad_ang <= rad_tot / 2)
	drawfloorceiling(&data->view3d);
	while (++x < WIN_W)
	{
		ray = init_ray(data->player, rad_ang);
		dist = ray_dist(data->map, data->player, &ray, rad_ang);
		orientation = compass(ray);
		draw3d(&data->view3d, dist, x, orientation);
		draw_line(data->player.pos, ray.pos, orientation, data);
		rad_ang += FOV / WIN_W;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->view3d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->view2d.img, 0, 0);
}

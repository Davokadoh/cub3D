/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/21 12:38:26 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

static t_cam	init_ray(t_cam player, double radius_angle, int doors)
{
	t_cam	ray;

	ray.angle = player.angle + radius_angle;
	ray.pos.x = player.pos.x;
	ray.pos.y = player.pos.y;
	ray.dir.x = cos(ray.angle);
	ray.dir.y = sin(ray.angle);
	ray.doors = doors;
	return (ray);
}

static int	check_wall(char **map, t_cam *ray, int ray_dir)
{
	double	dist_h;
	double	dist_v;

	dist_h = dist_next_h(*ray, ray_dir);
	dist_v = dist_next_v(*ray, ray_dir);
	if (dist_v <= dist_h)
	{
		ray->axis = 1;
		return (update_rayv(map, ray, ray_dir, dist_v));
	}
	else
	{
		ray->axis = 2;
		return (update_rayh(map, ray, ray_dir, dist_h));
	}
}

double	ray_dist(char **map, t_cam const player, t_cam *ray, double rad_ang)
{
	double	dist;
	int		dir_ray;

	dir_ray = ray_dir(*ray);
	while (check_wall(map, ray, dir_ray) < 1)
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
	if ((dir_ray == 3 || dir_ray == 4) && ray.axis == 2)
		return (1);
	else if ((dir_ray == 1 || dir_ray == 4) && ray.axis == 1)
		return (2);
	else if ((dir_ray == 1 || dir_ray == 2) && ray.axis == 2)
		return (3);
	else if ((dir_ray == 2 || dir_ray == 3) && ray.axis == 1)
		return (4);
	return (0);
}

t_cam	*cast_rays(t_data *data, t_cam *rays, int doors)
{
	double	rad_ang;
	int		x;

	x = -1;
	while (++x < WIN_W)
	{
		rad_ang = atan((x - WIN_W / 2) / (M_PI / 5) / WIN_W);
		rays[x] = init_ray(data->player, rad_ang, doors);
		rays[x].dist = ray_dist(data->map, data->player, &rays[x], rad_ang);
	}
	return (rays);
}

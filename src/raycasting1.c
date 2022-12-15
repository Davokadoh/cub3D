/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/15 16:31:12 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

int	ray_dir(t_cam ray)
{
	if (ray.dir.x >= 0 && ray.dir.y >= 0)
		return (1);
	if (ray.dir.x < 0 && ray.dir.y >= 0)
		return (2);
	if (ray.dir.x < 0 && ray.dir.y < 0)
		return (3);
	if (ray.dir.x >= 0 && ray.dir.y < 0)
		return (4);
	else
		return (0);
}

double	dist_next_h(t_cam ray, int ray_dir)
{
	double	dist;

	if (fmod(ray.angle, M_PI) == 0)
		return (MAXFLOAT);
	if (ray_dir > 2)
		dist = fabs((ray.pos.y - (int)ray.pos.y) / sin(ray.angle));
	else
		dist = (fabs((int)ray.pos.y + 1 - ray.pos.y) / sin(ray.angle));
	if (dist == 0)
		dist = fabs(1 / sin(ray.angle));
	return (dist);
}

double	dist_next_v(t_cam ray, int ray_dir)
{
	double	dist;

	if (fmod(ray.angle, M_PI_2) == 0 && fmod(ray.angle, M_PI) != 0)
		return (MAXFLOAT);
	if (ray_dir == 2 || ray_dir == 3)
		dist = fabs((ray.pos.x - (int)ray.pos.x) / cos(ray.angle));
	else
		dist = fabs(((int)ray.pos.x + 1 - ray.pos.x) / cos(ray.angle));
	if (dist == 0)
		dist = fabs(1 / cos(ray.angle));
	return (dist);
}

int	update_rayh(char **map, t_cam *ray, int ray_dir, double dist_h)
{
	int		int_x;
	int		int_y;

	ray->pos.x += cos(ray->angle) * dist_h;
	int_x = (int)(ray->pos.x);
	int_y = (int)(ray->pos.y);
	if (ray_dir > 2)
	{
		if (ray->pos.y == (double)int_y)
			ray->pos.y = (double)int_y - 1;
		else
			ray->pos.y = (double)int_y;
		if (map[(int)ray->pos.y - 1][int_x] == '1')
			return (1);
		else if (map[(int)ray->pos.y - 1][int_x] == 'D')
			return (1);
		else if (map[(int)ray->pos.y - 1][int_x] == 'c')
			return (1);
		else if (map[(int)ray->pos.y - 1][int_x] == 'o')
			return (1);
		return (0);
	}
	ray->pos.y = (double)(int_y + 1);
	if (map[(int)ray->pos.y][int_x] == '1')
		return (1);
	else if (map[(int)ray->pos.y][int_x] == 'D')
		return (1);
	else if (map[(int)ray->pos.y][int_x] == 'c')
		return (1);
	else if (map[(int)ray->pos.y][int_x] == 'o')
		return (1);
	return (0);
}

int	update_rayv(char **map, t_cam *ray, int ray_dir, double dist_v)
{
	int		int_x;
	int		int_y;

	ray->pos.y += sin(ray->angle) * dist_v;
	int_x = (int)ray->pos.x;
	int_y = (int)ray->pos.y;
	if (ray_dir == 2 || ray_dir == 3)
	{
		if (ray->pos.x == (double)int_x)
			ray->pos.x = (double)int_x - 1;
		else
			ray->pos.x = (double)int_x;
		//return (map[int_y][(int)ray->pos.x - 1] == '1' || map[int_y][(int)ray->pos.x - 1] == 'D');
		if (map[int_y][(int)ray->pos.x - 1] == '1')
			return (1);
		else if (map[int_y][(int)ray->pos.x - 1] == 'D')
			return (1);
		else if (map[int_y][(int)ray->pos.x - 1] == 'c')
			return (1);
		else if (map[int_y][(int)ray->pos.x - 1] == 'o')
			return (1);
		return (0);
	}
	ray->pos.x = (double)(int_x + 1);
	if (map[int_y][(int)ray->pos.x] == '1')
		return (1);
	else if (map[int_y][(int)ray->pos.x] == 'D')
		return (1);
	else if (map[int_y][(int)ray->pos.x] == 'c')
		return (1);
	else if (map[int_y][(int)ray->pos.x] == 'o')
		return (1);
	return (0);
}

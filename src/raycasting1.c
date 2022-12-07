/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/07 15:08:34 by jleroux          ###   ########.fr       */
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

float	dist_next_h(t_cam ray, int ray_dir)
{
	float	dist;

	printf("ray angle %f\n", ray.angle / DR );
	if (fmod(ray.angle, M_PI) == 0)
		return (MAXFLOAT);
	if (ray_dir > 2)
	{
		printf("ray.pos.y %f - fmod(ray.pos.y, 1) %d\n", ray.pos.y, (int)ray.pos.y);
		dist = fabs((ray.pos.y - (int)ray.pos.y) / sin(ray.angle));
	}
	else
	{
		dist = (fabs((int)ray.pos.y + 1 - ray.pos.y) / sin(ray.angle));
	}
	printf("dist h: %f\n", dist);
	if (dist == 0)
		dist = fabs(1 / sin(ray.angle));
	printf("dist h: %f\n", dist);
	return (dist);
}

float	dist_next_v(t_cam ray, int ray_dir)
{
	float	dist;

	if (fmod(ray.angle, M_PI_2) == 0 && fmod(ray.angle, M_PI) != 0)
		return (MAXFLOAT);
	if (ray_dir == 2 || ray_dir == 3)
	{
		dist = fabs((ray.pos.x - (int)ray.pos.x) / cos(ray.angle));
	}
	else
		dist = fabs(((int)ray.pos.x + 1 - ray.pos.x) / cos(ray.angle));
	printf("dist v: %f\n", dist);
	if (dist == 0)
		dist = fabs(1 / cos(ray.angle));
	printf("dist v: %f\n", dist);
	return (dist);
}

int	update_rayh(char **map, t_cam *ray, int ray_dir, float dist_h)
{
	int		int_x;
	int		int_y;

	int_x = (int)(ray->pos.x);
	int_y = (int)(ray->pos.y);
	ray->pos.x += cos(ray->angle) * dist_h;
	if (ray_dir > 2)
	{
		ray->pos.y = (float)int_y;
		printf("new ray->pos.y %f\n", ray->pos.y);
		printf("map[int_y][int_x] %c\n", map[int_y][int_x]);
		printf("map[int_y - 1][int_x] %c\n", map[int_y - 1][int_x + 1]);
		return (map[int_y - 1][int_x] == '1');
	}
	ray->pos.y = (float)(int_y + 1);
	printf("new ray->pos.y %f\n", ray->pos.y);
	printf("map[int_y][int_x] %c\n", map[int_y][int_x]);
	printf("map[int_y + 1][int_x] %c\n", map[int_y + 1][int_x + 1]);
	return (map[int_y + 1][int_x] == '1');
}

int	update_rayv(char **map, t_cam *ray, int ray_dir, float dist_v)
{
	int		int_x;
	int		int_y;

	int_x = (int)ray->pos.x;
	int_y = (int)ray->pos.y;
	ray->pos.y += sin(ray->angle) * dist_v;
	if (ray_dir == 2 || ray_dir == 3)
	{
		ray->pos.x = (float)int_x;
		printf("Anew ray->pos.x %f\n", ray->pos.x);
		printf("int_x %d\n", int_x);
		printf("int_y %d\n", int_y);
		printf("int_x - 1 %d\n", int_x - 1);
		printf("map[int_y][int_x] %c\n", map[int_y][int_x]);
		printf("map[int_y][int_x - 1] %c\n", map[int_y][int_x - 1]);
		return (map[int_y][int_x - 1] == '1');
	}
	ray->pos.x = (float)(int_x + 1);
	printf("new ray->pos.x %f\n", ray->pos.x);
	printf("map[int_y][int_x] %c\n", map[int_y][int_x]);
	printf("map[int_y][int_x + 1] %c\n", map[int_y][int_x + 1]);
	return (map[int_y][int_x + 1]== '1');
}

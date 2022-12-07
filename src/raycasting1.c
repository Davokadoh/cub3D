/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/07 13:18:30 by jleroux          ###   ########.fr       */
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
	printf("ray angle %f\n", ray.angle / DR );
	if (fmod(ray.angle, M_PI) == 0)
		return (MAXFLOAT);
	if (ray_dir > 2)
	{
		printf("ray.pos.y %f - fmod(ray.pos.y, 1) %d\n", ray.pos.y, (int)ray.pos.y);
		return (fabs((ray.pos.y - (int)ray.pos.y) / sin(ray.angle)));
	}
	return (fabs((int)ray.pos.y + 1 - ray.pos.y) / sin(ray.angle));
}

float	dist_next_v(t_cam ray, int ray_dir)
{
	if (fmod(ray.angle, M_PI_2) == 0 && fmod(ray.angle, M_PI) != 0)
		return (MAXFLOAT);
	if (ray_dir == 2 || ray_dir == 3)
	{
		return (fabs((ray.pos.x - (int)ray.pos.x) / cos(ray.angle)));
	}
	return (fabs(((int)ray.pos.x + 1 - ray.pos.x) / cos(ray.angle)));
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
		if (map[int_y][int_x] == '1')
			return (1);
		else
			return (0);
	}
	ray->pos.y = (float)(int_y + 1);
	if (map[int_y][int_x] == '1') 
		return (1);
	else
		return (0);
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
		if (map[int_y][int_x] == '1')
			return (1);
		else
			return (0);
	}
	ray->pos.x = (float)(int_x + 1);
	if (map[int_y][int_x] == '1')
		return (1);
	else
		return (0);
}

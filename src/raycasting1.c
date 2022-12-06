/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/06 17:15:58 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

int	ray_dir(t_cam ray)
{
	if (ray.pos.x >= 0 && ray.pos.y >= 0)
		return (1);
	if (ray.pos.x < 0 && ray.pos.y >= 0)
		return (2);
	if (ray.pos.x < 0 && ray.pos.y < 0)
		return (3);
	if (ray.pos.x >= 0 && ray.pos.y < 0)
		return (4);
	else
		return (0);
}

float	dist_next_h(t_cam ray, int ray_dir)
{
	if (fmod(ray.angle, M_PI) == 0)
		return (MAXFLOAT);
	if (ray_dir > 2)
	{
		return (ray.pos.y - fabs(ray.pos.y) / sin(ray.angle));
	}
	return (fabs(ray.pos.y) + 1 - ray.pos.y / sin(ray.angle));
}

float	dist_next_v(t_cam ray, int ray_dir)
{
	if (fmod(ray.angle,M_PI_2) == 0 && fmod(ray.angle, M_PI) != 0)
		return (MAXFLOAT);
	if (ray_dir == 2 || ray_dir == 3)
	{
		return (ray.pos.x - fabs(ray.pos.x) / cos(ray.angle));
	}
	return (fabs(ray.pos.x) + 1 - ray.pos.x / cos(ray.angle));
}

int	update_rayh(char **map, t_cam *ray, int ray_dir, float dist_h)
{
	int		abs_x;
	int		abs_y;

	abs_x = (int)(fabs(ray->pos.y));
	abs_y = (int)(fabs(ray->pos.x));
	ray->pos.x += cos(ray->angle) * dist_h;
	if (ray_dir > 2)
	{
		ray->pos.y += ray->pos.y - fabs(ray->pos.y);
		if (map[abs_x][abs_y - 1] == '1')
			return (1);
		else
			return (0);
	}
	ray->pos.y += fabs(ray->pos.y) + 1 - ray->pos.y;
	printf("[abs_x] %d[abs_y] %d  map[abs_x][abs_y + 1] %c\n", abs_x, abs_y, map[abs_x][abs_y + 1]);
	printf("update ray h: ray->angle %f,ray->pos.x%f, ray.pos.y%f, ray.dir.x%f, ray.dir.y%f \n", ray->angle, ray->pos.x,ray->pos.y, ray->dir.x, ray->dir.y );
	if (map[abs_x][abs_y + 1] == '1')
		return (1);
	else
		return (0);
}

int	update_rayv(char **map, t_cam *ray, int ray_dir, float dist_v)
{
	int		abs_x;
	int		abs_y;

	abs_x = (int)(fabs(ray->pos.y));
	abs_y = (int)(fabs(ray->pos.x));
	ray->pos.y += sin(ray->angle) * dist_v;
	if (ray_dir == 2 || ray_dir == 3)
	{
		ray->pos.x += ray->pos.x - fabs(ray->pos.x);
		if (map[abs_x - 1][abs_y] == '1')
			return (1);
		else
			return (0);
	}
	ray->pos.y += fabs(ray->pos.x) + 1 - ray->pos.x;
		printf("[abs_x] %d[abs_y] %d  map[abs_x][abs_y + 1] %c\n", abs_x, abs_y, map[abs_x][abs_y + 1]);
	printf("update ray v :ray.angle %f,ray.pos.x%f, ray.pos.y%f, ray.dir.x%f, ray.dir.y%f \n", ray->angle, ray->pos.x,ray->pos.y, ray->dir.x, ray->dir.y);
	if (map[abs_x + 1][abs_y] == '1')
		return (1);
	else
		return (0);
}

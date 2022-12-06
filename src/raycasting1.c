/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/07 00:27:29 by vhaefeli         ###   ########.fr       */
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
		printf("salut\n");
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
	printf("old ray->pos.x %f\n", ray->pos.x);
	printf("old ray->pos.y %f\n", ray->pos.y);
	ray->pos.x += cos(ray->angle) * dist_h;
	printf("new ray->pos.x %f\n", ray->pos.x);
	if (ray_dir > 2)
	{
		ray->pos.y = (float)int_y;
		printf("new ray->pos.y %f\n", ray->pos.y);
		if (map[int_x][int_y - 1] == '1')
			return (1);
		else
			return (0);
	}
	ray->pos.y = (float)(int_y + 1);
	printf("new ray->pos.y %f\n", ray->pos.y);
	printf("[abs_x] %d[abs_y] %d  map[abs_x][abs_y + 1] %c\n", int_x, int_y, map[int_x][int_y + 1]);
	printf("update ray h: ray->angle %f,ray->pos.x%f, ray.pos.y%f, ray.dir.x%f, ray.dir.y%f \n", ray->angle, ray->pos.x,ray->pos.y, ray->dir.x, ray->dir.y );
	if (map[int_x][int_y + 1] == '1') 
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
	printf("old ray->pos.y %f\n", ray->pos.y);
	printf("old ray->pos.x %f\n", ray->pos.x);
	ray->pos.y += sin(ray->angle) * dist_v;
	printf("new ray->pos.y %f\n", ray->pos.y);
	if (ray_dir == 2 || ray_dir == 3)
	{
		ray->pos.x = (float)int_x;
		printf("new ray->pos.x %f\n", ray->pos.x);
		if (map[int_x - 1][int_y] == '1')
			return (1);
		else
			return (0);
	}
	ray->pos.x = (float)(int_x + 1);
	printf("new ray->pos.x %f\n", ray->pos.x);
		printf("[abs_x] %d[abs_y] %d  map[abs_x][abs_y + 1] %c\n", int_x, int_y, map[int_x][int_y + 1]);
	printf("update ray v :ray.angle %f,ray.pos.x%f, ray.pos.y%f, ray.dir.x%f, ray.dir.y%f \n", ray->angle, ray->pos.x,ray->pos.y, ray->dir.x, ray->dir.y);
	if (map[int_x + 1][int_y] == '1')
		return (1);
	else
		return (0);
}

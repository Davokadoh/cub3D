/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/06 09:20:09 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

// typedef struct	s_cam
// {
// 	float	pos[2]; //Position vector
// 	float	dir[2]; //Looking direction verctor
// }				t_cam;

// typedef struct	s_data
// {
// 	void	*mlx;
// 	void	*win;
// 	char	**map;
// 	char	*textures[7];
// 	t_cam	camera;
// }				t_data;

float	raycasting(t_data *data, t_img minimap)
{
	data->camera.pos[0] = 4.0 * (MM_W/data->map_w);//pour test
	data->camera.pos[1] = 4.0 * (MM_W/data->map_w);//pour test
	data->camera.dir[0] = 0.0;//pour test
	data->camera.dir[1] = -1.0;//pour test

}
void	draw_walls();

int	ray_dir(t_cam ray)
{
	if (ray.pos[0] >= 0 && ray.pos[1] >= 0)
		return (1);
	if (ray.pos[0] < 0 && ray.pos[1] >= 0)
		return (2);
	if (ray.pos[0] < 0 && ray.pos[1] < 0)
		return (3);
	if (ray.pos[0] >= 0 && ray.pos[1] < 0)
		return (4);
}

t_cam	ini_ray(t_cam player, float radius_angle)
{
	float	angle;
	t_cam	ray;

	angle = atan(player.dir[1] / player.dir[0]) + radius_angle;
	ray.pos[0] = player.pos[0];
	ray.pos[1] = player.pos[1];
	ray.dir[0] = cos(angle);
	ray.dir[1] = sin(angle);
}

float	dist_next_h(t_cam ray, int ray_dir)
{
	float	angle;

	angle = atan(ray.dir[1] / ray.dir[0]); // a passer comme parametre pour eviter de calculer a chaque fois?
	if (ray_dir > 2)
	{
		return (ray.pos[1] - fabs(ray.pos[1]) / sin(angle));
	}
	return (fabs(ray.pos[1]) + 1 - ray.pos[1] / sin(angle));
}

float	dist_next_v(t_cam player, float radius_angle)
{
	int		dir_ray;
	float	angle;

	dir_ray = ray_dir(player.dir, radius_angle);// a passer comme parametre pour eviter de calculer a chaque fois?
	angle = atan(player.dir[1] / player.dir[0]) + radius_angle; // a passer comme parametre pour eviter de calculer a chaque fois?
	if (ray_dir == 2 || ray_dir == 3)
	{
		return (player.pos[0] - fabs(player.pos[0]) / sin(angle));
	}
	return (fabs(player.pos[0]) + 1 - player.pos[0] / sin(angle));
}

int	check_wall(char **map, t_cam *raypoint, float radius_angle)
{
	float	dist_h;
	float	dist_v;
	int		abs_x;
	int		abs_y;

	abs_x = (int)(fabs(raypoint->pos[1]));
	abs_y = (int)(fabs(raypoint->pos[0]));
	dist_h = dist_next_h(*raypoint, radius_angle);
	dist_v = dist_next_v(*raypoint, radius_angle);
	if (dist_h <= dist_v)
	{
		if (map[abs_x - 1][abs_y] == 1);
			raypoint.po
	}
}
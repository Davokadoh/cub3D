/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/05 18:04:17 by vhaefeli         ###   ########.fr       */
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

int	ray_dir(float dir[2], float radius_angle)
{
	float	x;
	float	y;
	float	angle_dir;

	angle_dir = asin(dir[1]) + radius_angle;
	x = cos(angle_dir);
	y = sin(angle_dir);
	if (x >= 0 && y >= 0)
		return (1);
	if (x < 0 && y >= 0)
		return (2);
	if (x < 0 && y < 0)
		return (3);
	if (x >= 0 && y < 0)
		return (4);
}

float	dist_next_h(t_cam player, float radius_angle)
{
	float	dist;
	int		dir_ray;

	dir_ray = ray_dir(player.dir, radius_angle);
	if (ray_dir > 2)
	{
		dist = (player.pos[1] - fabs(player.pos[1]) / ());
	}
}

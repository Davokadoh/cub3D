/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:50:05 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/06 11:23:16 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

int	check_wall(char **map, t_cam *ray, int ray_dir)
{
	float	dist_h;
	float	dist_v;
	int		abs_x;
	int		abs_y;

	abs_x = (int)(fabs(ray->pos.y));
	abs_y = (int)(fabs(ray->pos.x));
	dist_h = dist_next_h(*ray, ray_dir);
	dist_v = dist_next_v(*ray, ray_dir);
	if (dist_h <= dist_v)
		return (update_rayh(map, ray, ray_dir, dist_h));
	if (dist_v < dist_h)
		return (update_rayv(map, ray, ray_dir, dist_v));
}


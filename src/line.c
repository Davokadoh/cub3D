/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:03 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 14:54:12 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_line(t_vec2d a, t_vec2d b, int color, t_data *data)
{
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
	int		pixels;

	a.x *= wall_size(data);
	a.y *= wall_size(data);
	b.x *= wall_size(data);
	b.y *= wall_size(data);
	delta_x = b.x - a.x;
	delta_y = b.y - a.y;
	pixels = 1 + sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	x = a.x;
	y = a.y;
	while (pixels)
	{
		put_pixel_img(&data->view2d, (int)x, (int)y, color);
		x += delta_x;
		y += delta_y;
		--pixels;
	}
}

int	draw2d(t_data *data, t_cam rays[WIN_W])
{
	int	x;

	x = -1;
	while (++x < WIN_W)
		draw_line(data->player.pos, rays[x].pos, 0x00909090, data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:03 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/08 13:20:27 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(t_img *img, t_vec2d a, t_vec2d b, int color, t_data *data)
{
	double	x;
	double	y;
	double	deltaX;
	double	deltaY;
	int		pixels;

	a.x *= wall_size(data);
	a.y *= wall_size(data);
	b.x *= wall_size(data);
	b.y *= wall_size(data);
	deltaX = b.x - a.x;
	deltaY = b.y - a.y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	x = a.x;
	y = a.y;
	while (pixels)
	{
		put_pixel_img(img, (int)x, (int)y, color);
		x += deltaX;
		y += deltaY;
		--pixels;
	}
}

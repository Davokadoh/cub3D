/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:03 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 17:55:49 by vhaefeli         ###   ########.fr       */
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

	deltaX = b.x * wall_size(data) - a.x * wall_size(data);
	deltaY = b.y * wall_size(data) - a.y * wall_size(data);
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	x = a.x * wall_size(data);
	y = a.y * wall_size(data);
	while (pixels)
	{
		put_pixel_img(img, y, x, color);
		x += deltaX;
		y += deltaY;
		--pixels;
	}
}

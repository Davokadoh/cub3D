/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:03 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 15:21:26 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(t_img *img, t_vec2d a, t_vec2d b, int color)
{
	double	x;
	double	y;
	double	deltaX;
	double	deltaY;
	int		pixels;

	deltaX = b.x - a.x;
	deltaY = b.y - a.y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	x = a.x;
	y = a.y;
	while (pixels)
	{
		put_pixel_img(img, y, x, color);
		x += deltaX;
		y += deltaY;
		--pixels;
	}
}

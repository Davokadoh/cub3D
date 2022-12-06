/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:03 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 14:56:58 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	swap(t_vec2d *a, t_vec2d *b)
{
	t_vec2d	c;
	//Change vec2d to float and change just on coordinate

	c = *a;
	*a = *b;
	*b = c;
}

void	draw_line(t_img *img, t_vec2d a, t_vec2d b, int color)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	delta;

	put_pixel_img(img, a.y, a.x, color);
	put_pixel_img(img, b.y, b.x, color);
	if (a.x > b.x)
		swap(&a, &b);
	if (a.y > b.y)
		swap(&a, &b);
	dx = b.x - a.x;
	dy = b.y - a.y;
	delta = 2 * dy - dx;
	y = a.y;
	x = a.x;
	while (++x < b.x)
	{
		put_pixel_img(img, y, x, color);
		if (delta > 0)
		{
			y = y + 1;
			delta = delta - 2 * dx;
		}
		delta = delta + 2 * dy;
	}
}

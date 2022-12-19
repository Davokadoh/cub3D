/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:09:10 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/19 18:08:10 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawfloorceiling(t_img *img, t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y <= WIN_H / 2)
	{
		while (++x <= WIN_W)
			put_pixel_img(img, x, y, data->color_ceiling);
		x = -1;
	}
	while (++y <= WIN_H)
	{
		while (++x <= WIN_W)
			put_pixel_img(img, x, y, data->color_floor);
		x = -1;
	}
}

int	get_texel_x(t_data *data, t_cam ray)
{
	t_img	texture;
	int		orientation;
	int		x;

	orientation = compass(ray);
	texture = data->textures[orientation - 1];
	if (data->map[(int)ray.pos.y][(int)ray.pos.x] == 'D')
		texture = data->textures[4];
	if (orientation == 1)
		x = (int)(fmod(ray.pos.x, 1.0) * texture.w);
	if (orientation == 2)
		x = (int)(fmod(ray.pos.y, 1.0) * texture.w);
	if (orientation == 3)
		x = (int)((1 - fmod(ray.pos.x, 1.0)) * texture.w);
	if (orientation == 4)
		x = (int)((1 - fmod(ray.pos.y, 1.0)) * texture.w);
	return (x);
}

int	get_texel_y(t_img texture, float img_y, float wall_top, float line_height)
{
	int		y;

	y = (img_y - wall_top) * texture.h * 0.25 / line_height;
	return ((int)y);
}

unsigned int	get_texel(t_img texture, int x, int y)
{
	unsigned int	clr;

	clr = *(unsigned int *)(texture.addr + (y * texture.line_size + x)
			* (texture.bits_per_pixel / 8));
	return (clr);
}

void	draw3d(t_data *data, t_cam rays[WIN_W])
{
	t_wall	wall;
	t_vec2d	texel;
	t_img	texture;
	int		x;

	x = -1;
	while (++x < WIN_W)
	{
		wall.line_h = (WIN_H / rays[x].dist);
		texture = data->textures[compass(rays[x]) - 1];
		if (rays[x].c == 2) //Change 2 to HORIZONTAL macro
			if (data->map[(int)(rays[x].pos.y + 0.5 * rays[x].dir.y)][(int)(rays[x].pos.x)] == 'D')
				texture = data->textures[4];
		if (rays[x].c == 1) //Change 1 to VERTICAL macro
			if (data->map[(int)(rays[x].pos.y)][(int)(rays[x].pos.x + 0.5 * rays[x].dir.x)] == 'D')
				texture = data->textures[4];
		texel.x = get_texel_x(data, rays[x]);
		wall.top = -wall.line_h / 2 + WIN_H / 2;
		wall.bot = wall.line_h / 2 + WIN_H / 2;
		while (--wall.bot > wall.top)
		{
			texel.y = get_texel_y(texture, wall.bot, wall.top, wall.line_h);
			put_pixel_img(&data->view3d, x, (int)wall.bot,
				get_texel(texture, (int)texel.x, (int)texel.y));
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:09:10 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/19 11:10:36 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawfloorceiling(t_img *img, char *t_path[7])
{
	int	x;
	int	y;
	int	colorf;
	int	colorc;

	x = -1;
	y = -1;
	colorf = str_to_rgb_int(t_path[4]);
	colorc = str_to_rgb_int(t_path[5]);
	while (++y <= WIN_H / 2)
	{
		while (++x <= WIN_W)
			put_pixel_img(img, x, y, colorc);
		x = -1;
	}
	while (++y <= WIN_H)
	{
		while (++x <= WIN_W)
			put_pixel_img(img, x, y, colorf);
		x = -1;
	}
}

int	get_texel_x(t_data *data, t_cam ray)
{
	t_img	texture;
	int		orientation;
	int		x;
	char	c;

	orientation = compass(ray);
	c = data->map[(int)ray.pos.y][(int)ray.pos.x];
	texture = data->textures[orientation - 1];
	if (c == 'D')
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
	char	c;

	x = -1;
	while (++x < WIN_W)
	{
		c = data->map[(int)rays[x].pos.y][(int)rays[x].pos.x];
		wall.line_h = (WIN_H / rays[x].dist);
		texture = data->textures[compass(rays[x]) - 1];
		if (c == 'D')
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

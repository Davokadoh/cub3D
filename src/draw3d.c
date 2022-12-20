/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:09:10 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/20 16:51:06 by jleroux          ###   ########.fr       */
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

int	get_texel_x(t_img texture, t_cam ray)
{
	int		orientation;
	int		x;

	orientation = compass(ray);
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

	if (x > texture.h)
		return (0xFF000000); //Hex -> Macro
	clr = *(unsigned int *)(texture.addr + (y * texture.line_size + x)
			* (texture.bits_per_pixel / 8));
	return (clr);
}

t_img	extra_texture(t_data *data, t_img current_texture, t_cam ray)
{
	char	type;

	if (ray.c == 2)
		type = data->map[(int)(ray.pos.y + 0.5 * ray.dir.y)][(int)(ray.pos.x)];
	else
		type = data->map[(int)(ray.pos.y)][(int)(ray.pos.x + 0.5 * ray.dir.x)];
	if (type == 'D' && !ray.back)
		return (data->textures[4]);
	if (type == 'd' && !ray.back)
		return (data->textures[4]);
	else if (type == 'P')
		return (data->textures[5]);
	else if (type == 'A')
		return (data->textures[6]);
	else
		return (current_texture);
}

void	open_door(t_data *data, t_cam ray, t_img *texture)
{
	if (texture->frame > texture->w)
	{
		if (ray.c == 2)
			data->map[(int)(ray.pos.y + 0.5 * ray.dir.y)][(int)(ray.pos.x)] = 'd';
		else
			data->map[(int)(ray.pos.y)][(int)(ray.pos.x + 0.5 * ray.dir.x)] = 'd';
	}
}

void	draw3d(t_data *data, t_img *view, t_cam rays[WIN_W])
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
		texture = extra_texture(data, texture, rays[x]);
		texel.x = get_texel_x(texture, rays[x]);
		if (texture.addr == data->textures[4].addr)
		{
			texel.x += texture.frame;
			open_door(data, rays[x], &texture);
		}
		wall.top = -wall.line_h / 2 + WIN_H / 2;
		wall.bot = wall.line_h / 2 + WIN_H / 2;
		while (--wall.bot > wall.top)
		{
			texel.y = get_texel_y(texture, wall.bot, wall.top, wall.line_h);
			put_pixel_img(view, x, (int)wall.bot,
				get_texel(texture, (int)texel.x, (int)texel.y));
		}
	}
}

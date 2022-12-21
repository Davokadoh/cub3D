/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:09:10 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/21 14:53:57 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_texel_x(t_img texture, t_cam ray)
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

static int	get_texel_y(t_img tex, float img_y, float w_top, float line_height)
{
	int		y;

	y = (img_y - w_top) * tex.h * 0.25 / line_height;
	return ((int)y);
}

static unsigned int	get_color(t_img texture, int x, int y)
{
	unsigned int	clr;

	if (x > texture.h)
		return (0xFF000000);
	clr = *(unsigned int *)(texture.addr + (y * texture.line_size + x)
			* (texture.bpp / 8));
	return (clr);
}

static t_img	get_texture(t_data *data, t_cam rays)
{
	t_img	texture;

	texture = data->textures[compass(rays) - 1];
	if (rays.wall_type == 'D' || rays.wall_type == 'o' || rays.wall_type == 'c')
		texture = data->textures[4];
	if (rays.wall_type == 'P')
		texture = data->textures[5];
	if (rays.wall_type == 'A')
		texture = data->textures[6];
	return (texture);
}

void	draw3d(t_data *data, t_img *view, t_cam rays[WIN_W])
{
	t_wall	wall;
	t_vec2d	texel;
	t_img	texture;
	int		x;

	anim(data, &data->textures[4]);
	x = -1;
	while (++x < WIN_W)
	{
		wall.line_h = (WIN_H / rays[x].dist);
		texture = get_texture(data, rays[x]);
		texel.x = get_texel_x(texture, rays[x]);
		if (rays[x].wall_type == 'c' || rays[x].wall_type == 'o')
			texel.x += texture.frame;
		wall.top = -wall.line_h / 2 + WIN_H / 2;
		wall.bot = wall.line_h / 2 + WIN_H / 2;
		while (--wall.bot > wall.top)
		{
			texel.y = get_texel_y(texture, wall.bot, wall.top, wall.line_h);
			put_pixel_img(view, x, (int)wall.bot,
				get_color(texture, (int)texel.x, (int)texel.y));
		}
	}
}

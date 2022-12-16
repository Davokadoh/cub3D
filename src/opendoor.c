/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendoor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:08:10 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/16 16:29:28 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D"

int	moving_door_img(t_data *data, t_cam rays[WIN_W])
{
	float	wall_bot;
	float	wall_top;
	float	line_height;
	t_vec2d	texel;
	t_img	texture;
	int		x;
	char	c;

	x = -1;
	while (++x < WIN_W)
	{
		c = data->map[(int)rays[x].pos.y][(int)rays[x].pos.x];
		line_height = (WIN_H / rays[x].dist);
		if (c == 'D')
		{
			texture = data->textures[4];
		texel.x = get_texel_x(data, rays[x]);
		wall_top = -line_height / 2 + WIN_H / 2;
		wall_bot = line_height / 2 + WIN_H / 2;
		while (--wall_bot > wall_top)
		{
			texel.y = get_texel_y(texture, wall_bot, wall_top, line_height);
			if (c == 'D')
				put_pixel_img(&data->view3d, x, (int)wall_bot, get_texel(texture, (int)texel.x, (int)texel.y));
			else
				put_pixel_img(&data->view3d, x, (int)wall_bot, 0xFF000000);
		}
	}
}

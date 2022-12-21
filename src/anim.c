/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:24:54 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 14:53:41 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	anim(t_data *data, t_img *texture)
{
	size_t	y;
	size_t	x;

	y = -1;
	while (++y < data->map_h)
	{
		x = -1;
		while (++x < data->map_w)
		{
			if (data->map[y][x] == 'o')
				texture->frame += 0.01 * texture->w;
			if (data->map[y][x] == 'c')
				texture->frame -= 0.01 * texture->w;
			if (data->map[y][x] == 'o' && texture->frame > texture->w)
				data->map[y][x] = '-';
			if (data->map[y][x] == 'c' && texture->frame < 0)
			{
				texture->frame = 0;
				data->map[y][x] = 'D';
			}
		}
	}
}

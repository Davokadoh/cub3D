/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:24:54 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 13:26:38 by jleroux          ###   ########.fr       */
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
			if (data->map[y][x] == 'o') //opening
				texture->frame += 0.01 * texture->w;
			if (data->map[y][x] == 'c') //closing
				texture->frame -= 0.01 * texture->w;
			if (data->map[y][x] == 'o' && texture->frame > texture->w) //opening
				data->map[y][x] = '-'; //open
			if (data->map[y][x] == 'c' && texture->frame < 0) //closing
			{
				texture->frame = 0;
				data->map[y][x] = 'D'; //closed
			}
		}
	}
}

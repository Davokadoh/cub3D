/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:28:55 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/14 14:18:49 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	calculate_minimap(t_data *data)
{
	init_img(data->mlx, &data->minimap, MM_W, MM_H);
	flood_img(&data->minimap, 0xFF000000); //Hex -> macro def
	draw_minimap(data, &data->minimap);
	return (0);
}

int	wall_size(t_data *map)
{
	map->map_w = ft_strlen(map->map[0]);
	map->map_h = 0;
	while (map->map[map->map_h])
		map->map_h++;
	if ((MM_W / map->map_w) <= (MM_H / map->map_h))
		return (MM_W / map->map_w);
	return (MM_H / map->map_h);
}

void	draw_minimap(t_data *map, t_img *minimap)
{
	int	x;
	int	y;
	int	wallsize;

	y = 0;
	wallsize = wall_size(map);
	while (y < MM_H)
	{
		if (map->map[y / wallsize] == NULL)
			break ;
		x = -1;
		while (++x < MM_W)
		{
			if (map->map[0][x / wallsize] == '\0')
				break ;
			if (map->map[y / wallsize][x / wallsize] == '1')
				put_pixel_img(minimap, x, y, 0x00333333);
			else if (map->map[y / wallsize][x / wallsize] == '0')
				put_pixel_img(minimap, x, y, 0x00FFFFFF);
		}
		y++;
	}
}

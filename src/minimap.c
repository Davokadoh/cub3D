/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:28:55 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/07 16:55:48 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	calculate_minimap(t_data *data)
{
	t_img minimap;

	minimap.img = mlx_new_image(data->mlx, MM_W, MM_H);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bits_per_pixel,
			&minimap.line_size, &minimap.endian);
	init_img(&minimap, MM_W, MM_H);
	draw_minimap(data, &minimap);
	return (minimap);
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

void	init_img(t_img *img, int width, int height)
{
	int		x;
	int		y;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			put_pixel_img(img, x, y, 0xFF000000);
	}
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
				put_pixel_img(minimap, x, y, 0x000000FF);
			else if (map->map[y / wallsize][x / wallsize] == '0')
				put_pixel_img(minimap, x, y, 0x00FFFFFF);
		}
		y++;
	}
}

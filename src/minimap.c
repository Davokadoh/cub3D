/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:28:55 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/12/02 14:53:30 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_minimap(t_data *data, t_img *minimap)
{
	data->map = malloc(2048);

	data->map[0] = "11111111111111111111";
	data->map[1] = "10000000000000000001";
	data->map[2] = "10110000000000000001";
	data->map[3] = "10000000000000000001";
	data->map[4] = "1000N000000000000001";
	data->map[5] = "10000000000000001111";
	data->map[6] = "10000000000000000001";
	data->map[7] = "11111100000000010001";
	data->map[8] = "10000000000000010001";
	data->map[9] = "11111111111111111111";
	data->map[10] = NULL;

	minimap->img = mlx_new_image(data->mlx, MM_W, MM_H);
	minimap->addr = mlx_get_data_addr(minimap->img, &minimap->bits_per_pixel ,
		&minimap->line_size, &minimap->endian);
	ini_img(minimap, MM_W, MM_H);
	draw_minimap(data, minimap);
	mlx_put_image_to_window(data->mlx, data->win, minimap->img, 0, 0);
}

int	wall_size(t_data *map)
{
	map->map_w = ft_strlen(map->map[0]);
	map->map_h = 0;
	printf("map->map_w %lu, map->map_h %lu", map->map_w, map->map_h);
	while (map->map[map->map_h])
		map->map_h++;
	printf("map->map_w %lu, map->map_h %lu", map->map_w, map->map_h);
	if ((MM_W / map->map_w) <= (MM_H / map->map_h))
		return (MM_W / map->map_w);
	return (MM_H / map->map_h);
}

void	ini_img(t_img *img, int width, int height)
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
	int 	x;
	int 	y;
	int 	wallsize;
	int		out;


	y = 0;
	wallsize = wall_size(map);
	out = MM_W;
	while (y < MM_H)
	{
		if (map->map[y / wallsize] == NULL)
			break;
		x = -1;
		while (++x < out)
		{
			if (map->map[0][x / wallsize] == '\0')
			{
				out = x;
				break;
			}
			if (map->map[y / wallsize][x / wallsize] == '1')
			{
				put_pixel_img(minimap, x, y, 0x00000FFF);
			}
			else if (map->map[y / wallsize][x / wallsize] == '0')
				put_pixel_img(minimap, x, y, 0x00FFFFFF);
			else
				put_pixel_img(minimap, x, y, 0x0000FFFF);
		}
		printf("\n");
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:33:30 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 14:57:12 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_floor_ceiling(t_img *img, t_data *data)
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

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIN_W && y < WIN_H)
		*(unsigned int *)(img->addr
				+ (y * img->line_size + x * img->bpp / 8)) = color;
}

int	fill_img(t_img *img, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < img->h)
	{
		x = -1;
		while (++x < img->w)
			put_pixel_img(img, x, y, color);
	}
	return (0);
}

int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_size, &img->endian);
	img->h = height;
	img->w = width;
	return (0);
}

int	render(t_data *data)
{
	t_cam	rays[WIN_W];
	t_cam	rays_doors[WIN_W];

	init_img(data->mlx, &data->view2d, MM_W, MM_H);
	init_img(data->mlx, &data->view3d, WIN_W, WIN_H);
	init_img(data->mlx, &data->view_doors, WIN_W, WIN_H);
	fill_img(&data->view2d, 0xFF000000);
	fill_img(&data->view_doors, 0xFF000000);
	draw_floor_ceiling(&data->view3d, data);
	cast_rays(data, rays, 0);
	cast_rays(data, rays_doors, 1);
	draw2d(data, rays);
	draw3d(data, &data->view3d, rays);
	draw3d(data, &data->view_doors, rays_doors);
	mlx_put_image_to_window(data->mlx, data->win, data->view3d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->view_doors.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->view2d.img, 0, 0);
	mlx_destroy_image(data->mlx, data->view2d.img);
	mlx_destroy_image(data->mlx, data->view3d.img);
	mlx_destroy_image(data->mlx, data->view_doors.img);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:33:30 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/20 16:53:40 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3D.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIN_W && y < WIN_H)
		*(unsigned int *)(img->addr
				+ (y * img->line_size + x * img->bits_per_pixel / 8)) = color;
}

int	flood_img(t_img *img, int color)
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
	// if (img->img == NULL)
	// 	return (1); //Change to (clean_)exit() ?
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_size, &img->endian);
	img->h = height;
	img->w = width;
	// do more error checking here
	return (0);
}

static int	draw2d(t_data *data, t_cam rays[WIN_W])
{
	int	x;

	x = -1;
	while (++x < WIN_W)
		draw_line(data->player.pos, rays[x].pos, 0x00909090, data); //Hex -> macro def
	return (0);
}

void	anim(t_img *texture)
{
	if (texture->state == '(')
		texture->frame += 100;
	else if (texture->state == ')')
		texture->frame -= 100;
	if (texture->frame > texture->w)
		texture->frame = texture->w + 100;
	else if (texture->frame < 0)
	{
		texture->frame = 0;
		texture->state = 0;
	}
}

int	render(t_data *data)
{
	t_cam	rays[WIN_W];
	t_cam	rays_back[WIN_W];

	anim(&data->textures[4]);
	init_img(data->mlx, &data->view2d, MM_W, MM_H);
	init_img(data->mlx, &data->view3d, WIN_W, WIN_H);
	init_img(data->mlx, &data->view3dback, WIN_W, WIN_H);
	flood_img(&data->view2d, 0xFF000000); //Hex -> macro def
	flood_img(&data->view3d, 0xFF000000); //Hex -> macro def
	drawfloorceiling(&data->view3dback, data);
	cast_rays(data, rays, 0);
	cast_rays(data, rays_back, 1);
	draw2d(data, rays);
	draw3d(data, &data->view3d, rays);
	draw3d(data, &data->view3dback, rays_back);
	mlx_put_image_to_window(data->mlx, data->win, data->view3dback.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->view3d.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->view2d.img, 0, 0);
	mlx_destroy_image(data->mlx, data->view2d.img);
	mlx_destroy_image(data->mlx, data->view3d.img);
	mlx_destroy_image(data->mlx, data->view3dback.img);
	return (0);
}

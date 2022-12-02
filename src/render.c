/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:33:30 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/02 15:36:53 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3D.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIN_W && y < WIN_H)
		*(unsigned int *)(img->addr +
				(y * img->line_size + x * img->bits_per_pixel / 8)) = color;
}

static int	get_color()
{
	return (0x00FF0000);
}

void	render(t_data *data)
{
	int		x;
	int		y;
	t_img	img;

	img.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size,
								&img.endian);
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			put_pixel_img(&img, x, y, get_color());
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
}

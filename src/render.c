/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:33:30 by jleroux           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/07 14:09:23 by vhaefeli         ###   ########.fr       */
=======
/*   Updated: 2022/12/07 13:07:54 by jleroux          ###   ########.fr       */
>>>>>>> 3ccb063d560818fb391caaa9360df94070450333
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

void	render(t_data *data)
{
	t_img	img;

	draw_line(&img, (t_vec2d){WIN_H, WIN_W}, (t_vec2d){0, 0}, 0x000000, data);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	view_field(data, FOV);
}

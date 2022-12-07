/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:33:30 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/07 15:03:36 by jleroux          ###   ########.fr       */
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
	view_field(data, FOV);
}

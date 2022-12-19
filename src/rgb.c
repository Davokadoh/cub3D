/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:10:16 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/19 11:44:50 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rgb_to_int(int r, int g, int b)
{
	int	color;

	color = 0;
	color |= (int)(b);
	color |= (int)(g) << 8;
	color |= (int)(r) << 16;
	return (color);
	//See mlx_get_color()
}

int	str_to_rgb_int(char *str_rgb)
{
	char	**rgb;
	int		color;

	rgb = ft_split(str_rgb, ',');
	color = rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	ft_free_tab(rgb);
	return (color);
}

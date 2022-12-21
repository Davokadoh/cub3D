/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:10:16 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 14:52:50 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_colors(t_data *data)
{
	data->color_floor = str_to_rgb_int(data->paths[0]);
	if (data->color_floor == -1)
		return (1);
	data->color_ceiling = str_to_rgb_int(data->paths[1]);
	if (data->color_ceiling == -1)
		return (1);
	return (0);
}

static int	rgb_to_int(int r, int g, int b)
{
	int	color;

	color = 0;
	color |= (int)(b);
	color |= (int)(g) << 8;
	color |= (int)(r) << 16;
	return (color);
}

static int	checkintcolor(char **rgb, int (*intrgb)[3])
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (rgb[n] && n < 3)
	{
		while ((rgb[n][i]))
		{
			if (!ft_isdigit(rgb[n][i]))
				return (-1);
			i++;
		}
		i = 0;
		(*intrgb)[n] = ft_atoi(rgb[n]);
		if ((*intrgb)[n] < 0 || (*intrgb)[n] > 255)
			break ;
		n++;
	}
	if (n != 3 && rgb[n])
		return (-1);
	return (0);
}

int	str_to_rgb_int(char *str_rgb)
{
	char	**rgb;
	int		color;
	int		intrgb[3];

	rgb = ft_split(str_rgb, ',');
	if (!rgb && !*rgb)
		return (-1);
	if (checkintcolor(rgb, &intrgb))
	{
		ft_free_tab(rgb);
		return (-1);
	}
	color = rgb_to_int(intrgb[0], intrgb[1], intrgb[2]);
	ft_free_tab(rgb);
	return (color);
}

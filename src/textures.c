/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:37 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/20 17:00:55 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

int	init_texture(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		data->textures[i].img = mlx_xpm_file_to_image(data->mlx,
				data->paths[i], &data->textures[i].h, &data->textures[i].w);
		if (data->textures[i].img == NULL)
			return (put_error(data, "texture error", 7));
		data->textures[i].addr = mlx_get_data_addr(data->textures[i].img,
				&data->textures[i].bits_per_pixel,
				&data->textures[i].line_size, &data->textures[i].endian);
	}
	while (i < 7 && data->paths[i +2])
	{
		data->textures[i].img = mlx_xpm_file_to_image(data->mlx,
				data->paths[i + 2], &data->textures[i].h, &data->textures[i].w);
		if (data->textures[i].img == NULL)
			return (put_error(data, "texture error", 7));
		data->textures[i].addr = mlx_get_data_addr(data->textures[i].img,
				&data->textures[i].bits_per_pixel,
				&data->textures[i].line_size, &data->textures[i].endian);
		i++;
	}
	return (0);
}

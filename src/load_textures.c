/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:03:49 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/15 14:29:48 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_img	load_from_file(void *mlx, char *path)
{
	t_img	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.h, &texture.w);
	if (texture.img == NULL)
	{
		put_error("Mlx can't load texture", 7);
		return (texture);
	}
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
			&texture.line_size, &texture.endian);
	// if (!addr)
	return (texture);
}

int	load_all_textures(t_data *data, t_sprt *dst, char **path)
{
	unsigned int	i;

	i = 0;
	data->sprite[i] = load_from_file(&data->mlx, path);
	while (data->sprite[i++])
		data->sprite[i] = load_from_file(&data->mlx, path);
}

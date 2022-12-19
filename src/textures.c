/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:37 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/20 00:21:17 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

void	textures_init(char *t_path[7])
{
	int	i;

	i = -1;
	while (++i < 7)
		t_path[i] = NULL;
}

static int	get_texture_index(char *line)
{
	if (!ft_strncmp("NO", line, 2))
		return (0);
	else if (!ft_strncmp("SO", line, 2))
		return (1);
	else if (!ft_strncmp("WE", line, 2))
		return (2);
	else if (!ft_strncmp("EA", line, 2))
		return (3);
	else if (!ft_strncmp("F", line, 1))
		return (4);
	else if (!ft_strncmp("C", line, 1))
		return (5);
	else
		return (6);
}

static int	add_path(char *line, char *t_path[7])
{
	char	**splited;
	int		index;

	if (*line == '\n')
		return (0);
	splited = ft_split(line, ' ');
	index = get_texture_index(splited[0]);
	if (splited[1])
	{
		if (t_path[index])
			return (printf("A texture is defined twice\n"));
		t_path[index] = ft_strdup(splited[1]);
		t_path[index][ft_strlen(t_path[index]) - 1] = '\0';
	}
	ft_free_tab(splited);
	return (0);
}

int	free_textures(char *t_path[7])
{
	int	i;

	i = -1;
	while (++i < 6) //t_path[6] n'est pas forcement a NULL car utilise pour le controle d'erreur mais il n-est jamais malloc donc ne doit pas etre free
	{
		printf("free(t_path[%d] %s\n", i, t_path[i]);
		ft_free(t_path[i]);
	}
	return (1);
}

int	init_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures[i].img = mlx_xpm_file_to_image(data->mlx,
				data->t_path[i], &data->textures[i].h, &data->textures[i].w);
		if (data->textures[i].img == NULL)
			return (put_error(data, "texture error", 7));
		data->textures[i].addr = mlx_get_data_addr(data->textures[i].img,
				&data->textures[i].bits_per_pixel,
				&data->textures[i].line_size, &data->textures[i].endian);
		i++;
	}
	data->textures[4].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/porterouge.xpm", &data->textures[4].h, &data->textures[4].w);
	if (data->textures[4].img == NULL)
		return (put_error(data, "texture error", 7));
	data->textures[4].addr = mlx_get_data_addr(data->textures[4].img,
			&data->textures[4].bits_per_pixel,
			&data->textures[4].line_size, &data->textures[4].endian);
	data->textures[5].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/perenoel.xpm", &data->textures[5].h, &data->textures[5].w);
	if (data->textures[5].img == NULL)
		return (put_error(data, "texture error", 7));
	data->textures[5].addr = mlx_get_data_addr(data->textures[5].img,
			&data->textures[5].bits_per_pixel,
			&data->textures[5].line_size, &data->textures[5].endian);
	return (0);
}

int	get_textures(char *file_path, size_t map_start, char *t_path[7])
{
	char	*line;
	size_t	line_nbr;
	int		fd;

	line_nbr = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (printf("Can't open file\n"));
	line = get_next_line(fd);
	while (line != NULL && line_nbr < map_start)
	{
		if (add_path(line, t_path))
			return (1);
		free(line);
		line = get_next_line(fd);
		line_nbr++;
	}
	free(line);
	if (!t_path[0] || !t_path[1] || !t_path[2] || !t_path[3]
		|| !t_path[4] || !t_path[5])
		t_path[6] = "1";
	close(fd);
	return (t_path[6] != NULL);
}

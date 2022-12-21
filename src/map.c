/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:02 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 14:52:36 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static size_t	max_length(char **map)
{
	int		i;
	size_t	len;
	size_t	max;

	max = 0;
	i = -1;
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
	}
	return (max - 1);
}

static void	fill_line(char **line, size_t max)
{
	size_t		i;
	char		*filled_line;

	filled_line = malloc(max * sizeof(char *));
	i = ft_strlcpy(filled_line, *line, ft_strlen(*line)) - 1;
	while (i < max)
		filled_line[i++] = ' ';
	filled_line[i] = 0;
	free(*line);
	*line = filled_line;
}

static void	fill_map(char ***map)
{
	int		i;
	size_t	max;

	max = max_length(*map);
	i = -1;
	while ((*map)[++i])
		fill_line(&(*map)[i], max);
}

static int	get_from_file(char *f_path, size_t map_start,
		size_t map_end, char ***map)
{
	int	y;
	int	fd;

	fd = open(f_path, O_RDONLY);
	if (fd < 0)
		return (printf("MAP\n"));
	y = -1;
	while (++y <= (int)map_start)
		free(get_next_line(fd));
	(*map) = malloc((map_end - map_start) * sizeof(char **));
	y = -1;
	(*map)[++y] = get_next_line(fd);
	while ((*map)[y] != NULL)
		(*map)[++y] = get_next_line(fd);
	return (0);
}

int	get_map(char *file_path, size_t map_start, size_t map_end, t_data *data)
{
	if (get_from_file(file_path, map_start, map_end, &data->map))
		return (1);
	fill_map(&data->map);
	if (check_closed_map(data->map, data->paths))
		return (printf("Map not closed\n"));
	data->map_w = max_length(data->map);
	data->map_h = map_end - map_start;
	return (0);
}

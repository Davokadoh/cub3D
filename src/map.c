/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:02 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/30 17:32:08 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

static int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

static int	check_around(char **map, int y, int x)
{
	int	i;
	int	j;

	i = -1;
	while (i < 2)
	{
		if (y + i < 0 || !map[y + i])
			return (1);
		j = -1;
		while (j < 2)
		{
			if (x + j < 0 || !map[y + i][x + j])
				return (1);
			else if (!is_map_char(map[y + i][x + j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

//Check around each 0 cell
static int	check_closed_map(char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if (check_around(map, y, x))
					return (1);
			}
		}
	}
	return (0);
}

/*
static void	print_map(char **map)
{
	int	x;

	x = -1;
	while (map[++x])
		printf("%i %s\\n\n", x, map[x]);
}
*/

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
	return (max);
}

static void	fill_line(char **line, size_t max)
{
	int		i;
	char	*filled_line;

	filled_line = malloc(max * sizeof(char *));
	i = ft_strlcpy(filled_line, *line, ft_strlen(*line)) - 1;
	/* Just in case
	while(i < max)
		filled_line[i++] = 'A';
	filled_line[i++] = '\0';
	*/
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

static int	get_from_file(char *file_path, size_t map_start,
		size_t map_end, char ***map)
{
	int	y;
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (put_error("MAP", 1));
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

int	get_map(char *file_path, size_t map_start, size_t map_end, char ***map)
{
	if (get_from_file(file_path, map_start, map_end, map))
		return (1);
	fill_map(map);
	//print_map(*map);
	if (check_closed_map(*map))
		return (put_error("Map not closed", 8));
	return (0);
}

/*
int	get_map(char *file_path, size_t map_start, char ***map)
{
	char	**tmp_map;

	(void) file_path;
	(void) map_start;
	tmp_map = malloc(2048);

	tmp_map[0] = "1111 11111";
	tmp_map[1] = "1001 10001";
	tmp_map[2] = "1001 10001";
	tmp_map[3] = "1001110001";
	tmp_map[4] = "1000000001";
	tmp_map[5] = "1000000001";
	tmp_map[6] = "1000N00001";
	tmp_map[7] = "1000000001";
	tmp_map[8] = "1000000001";
	tmp_map[9] = "1111111111";
	tmp_map[10] = NULL;

	*map = tmp_map;
	print_map(*map);
	if (check_closed_map(*map))
		return (put_error("Map not closed", 8));
	return (0);
}
*/

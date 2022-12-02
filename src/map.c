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

static int	check_around(char **map, int y, int x)
{
	int i;
	int j;

	i = -1;
	while (map[y + i] && i < 2)
	{
		j = -1;
		while (map[y + i][x + j] && j < 2)
		{
			if (map[y + i][x + j] != '1' && map[y + i][x + j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	print_map(char **map)
{
	int	x;

	x = -1;
	while (map[++x])
		printf("%i %s\n", x, map[x]);
}

static int	check_closed_map(char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == ' ')
				if (check_around(map, x, y))
					return (1);
	}
	return (0);
}

int	get_map(int fd, char ***map)
{
	char	**tmp_map;

	tmp_map = malloc(2048);

	tmp_map[0] = "1111111111";
	tmp_map[1] = "1000000001";
	tmp_map[2] = "1000000001";
	tmp_map[3] = "1000000001";
	tmp_map[4] = "1000N00001";
	tmp_map[5] = "1000000001";
	tmp_map[6] = "1000000001";
	tmp_map[7] = "1000000001";
	tmp_map[8] = "1000000001";
	tmp_map[9] = "1111111111";
	tmp_map[10] = NULL;

	(void) fd;
	*map = tmp_map;
	print_map(*map);
	if (check_closed_map(*map))
		return (put_error("Map not closed", 8));
	return (0);
}

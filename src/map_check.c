/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:02 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 18:01:22 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_map_char(char c, char **paths)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E')
		return (1);
	if (c == 'D' && paths[6])
		return (1);
	if (c == 'P' && paths[7])
		return (1);
	if (c == 'A' && paths[8])
		return (1);
	printf("caracter not allowed or not defined in map\n");
	return (0);
}

static int	check_around(char **map, int y, int x, char **paths)
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
			else if (!is_map_char(map[y + i][x + j], paths))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_closed_map(char **map, char **paths)
{
	int	x;
	int	y;

	if (!map)
		return (1);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != ' ')
			{
				if (check_around(map, y, x, paths))
					return (1);
			}
		}
	}
	return (0);
}

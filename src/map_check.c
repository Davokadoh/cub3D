/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:02 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/20 16:23:52 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == 'D' || c == 'P' || c == 'A')
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

int	check_closed_map(char **map)
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
				if (check_around(map, y, x))
					return (1);
			}
		}
	}
	return (0);
}

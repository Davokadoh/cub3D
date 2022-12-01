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

#include "libft.h"

//Needs to actually check around...
static int	check_around(char **map, int x, int y)
{
	if (map[x][y] != '1' && map[x][y] != ' ')
		return (1);
	return (0);
}

static int	check_closed_map(char **map)
{
	int	x;
	int	y;

	x = -1;
	while (map[++x][0])
	{
		y = -1;
		while (map[x][++y])
			if (map[x][y] == ' ')
				if (check_around(map, x, y))
					return (1);
	}
	return (0);
}

int	get_map(int fd, char **map)
{
	char	**tmp_map =	{"111111111",\
						 "100000001",\
						 "101100001",\
						 "100000001",\
						 "1000N0001",\
						 "100000001",\
						 "100000001",\
						 "100000001",\
						 "100000001",\
						 "111111111"};

	(void) fd;
	map = tmp_map;
	if (check_closed_map(map))
		return (1);
	return (0);
}

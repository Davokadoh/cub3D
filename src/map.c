/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:02 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/02 14:14:58 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Needs to actually check around...
static int	check_around(char **map, int x, int y)
{
	if (map[x][y] != '1' && map[x][y] != ' ')
		return (1);
	return (0);
}

// static void	print_map(char **map)
// {
// 	int	x;

// 	x = -1;
// 	printf("HELLO\n");
// 	while (map[++x])
// 	{
// 		printf("HELLO\n");
// 		printf("%i %s\n", x, map[x]);
// 	}
// 	printf("BYE\n");
// }

// static int	check_closed_map(char **map)
// {
// 	int	x;
// 	int	y;

// 	x = -1;
// 	while (map[++x][0])
// 	{
// 		y = -1;
// 		while (map[x][++y])
// 			if (map[x][y] == ' ')
// 				if (check_around(map, x, y))
// 					return (1);
// 	}
// 	return (0);
// }

int	get_map(int fd, char ***map)
{
	char	**tmp_map;

	tmp_map = malloc(2048);

	tmp_map[0] = "1111111111";
	tmp_map[1] = "1000000001";
	tmp_map[2] = "1011000001";
	tmp_map[3] = "1000000001";
	tmp_map[4] = "1000N00001";
	tmp_map[5] = "1000000001";
	tmp_map[6] = "1000000001";
	tmp_map[7] = "1000000001";
	tmp_map[8] = "1000000001";
	tmp_map[9] = "1111111111";
	tmp_map[10] = NULL;

	(void) fd;
	map = tmp_map;
	// print_map(map);
	// // if (check_closed_map(map))
	// // 	return (1);
	return (0);
}

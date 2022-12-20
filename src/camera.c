/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:25:18 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/20 15:54:33 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_unique_player(char **map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	j = -1;
	while (map[++j] != NULL)
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
				|| map[j][i] == 'W')
			player ++;
		}
	}
	if (player == 1)
		return (0);
	return (1);
}

static t_vec2d	get_pos(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
					map[i][j] == 'W' || map[i][j] == 'E')
				return (new_vec(j, i));
		}
	}
	return (new_vec(i, j));
}

static t_vec2d	get_dir(char c)
{
	t_vec2d	dir;

	if (c == 'N')
		dir = new_vec(0, -1);
	else if (c == 'S')
		dir = new_vec(0, 1);
	else if (c == 'W')
		dir = new_vec(-1, 0);
	else if (c == 'E')
		dir = new_vec(1, 0);
	else
		dir = new_vec(0, 0);
	return (dir);
}

static double	get_angle(char c)
{
	double	angle;

	if (c == 'N')
		angle = 3 * M_PI_2;
	else if (c == 'S')
		angle = M_PI_2;
	else if (c == 'W')
		angle = M_PI;
	else if (c == 'E')
		angle = 0;
	else
		angle = 0;
	return (angle);
}

int	get_player(t_data *data)
{
	t_vec2d	pos;

	if (check_unique_player(data->map))
		return (printf("There is more or less than one \
player defined by N, E, S or W\n"));
	pos = get_pos(data->map);
	data->player.pos = pos;
	data->player.pos.x += 0.5;
	data->player.pos.y += 0.5;
	data->player.dir = get_dir(data->map[(int)pos.y][(int)pos.x]);
	data->player.angle = get_angle(data->map[(int)pos.y][(int)pos.x]);
	data->map[(int)floor(pos.y)][(int)floor(pos.x)] = '0';
	return (0);
}

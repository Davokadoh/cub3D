/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:25:18 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 16:06:07 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3D.h"

//Doesn't check if multiple instance on same line
static int	get_player_in_line(char *line)
{
	if (ft_strchr(line, 'N'))
		return (1);
	else if (ft_strchr(line, 'S'))
		return (1);
	else if (ft_strchr(line, 'W'))
		return (1);
	else if (ft_strchr(line, 'E'))
		return (1);
	else
		return (0);
}

static int	check_unique_player(char **map)
{
	int		i;
	int		player;
	int		new_player;

	player = 0;
	i = -1;
	while (map[++i] != NULL)
	{
		new_player = get_player_in_line(map[i]);
		if (player && new_player)
			return (1);
		player = new_player;
	}
	return (player);
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

int	get_player(t_data *data)
{
	t_vec2d	pos;

	if (check_unique_player(data->map))
		return (put_error("", 7));
	pos = get_pos(data->map);
	data->player.pos = pos;
	data->player.dir = get_dir(data->map[(int)floor(pos.y)][(int)floor(pos.x)]);
	printf("avant angle\n");
	data->player.angle = atan(data->player.dir.y / data->player.dir.x);
	printf("angle:%f\n", data->player.angle);
	return (0);
}

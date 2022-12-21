/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:15 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 12:07:15 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "keys.h"

int	turn_left(t_data *data)
{
	data->player.angle -= (M_PI / 180);
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	return (1);
}

int	turn_right(t_data *data)
{
	data->player.angle += (M_PI / 180);
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	return (1);
}

int	open_close_door(t_data *data, int key)
{
	float	px;
	float	py;
	float	dx;
	float	dy;
	int		space;

	space = KEY_SPACE;
	px = data->player.pos.x;
	py = data->player.pos.y;
	dx = data->player.dir.x;
	dy = data->player.dir.y;
	if (key == space && data->map[(int)(py + dy)][(int)(px + dx)] == 'D')
		data->map[(int)(py + dy)][(int)(px + dx)] = 'o';
	else if (key == space && data->map[(int)(py + dy)][(int)(px + dx)] == '-')
		data->map[(int)(py + dy)][(int)(px + dx)] = 'c';
	else if (key == space && data->map[(int)(py + 2 * dy)][(int)(px + 2 * dx)]
			== 'D')
		data->map[(int)(py + 2 * dy)][(int)(px + 2 * dx)] = 'o';
	else if (key == space && data->map[(int)(py + 2 * dy)][(int)(px + 2 * dx)]
			== '-')
		data->map[(int)(py + 2 * dy)][(int)(px + 2 * dx)] = 'c';
	else
		return (1);
	return (0);
}

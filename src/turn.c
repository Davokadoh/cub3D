/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:26:15 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/12 16:00:01 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "keys.h"

int	turn_left(t_data *data)
{
	data->player.angle -= 4 * DR;
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	return (1);
}

int	turn_right(t_data *data)
{
	data->player.angle += 4 * DR;
	data->player.dir.x = cos(data->player.angle);
	data->player.dir.y = sin(data->player.angle);
	return (1);
}

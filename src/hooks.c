/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:15:53 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/30 17:17:11 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "keys.h"
#include "cub3D.h"

int	hook_keydown(int key, t_data data)
{
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	if (move(key, data))
		render(data);
}

int	hook_mousemove(int key, t_data data)
{
}

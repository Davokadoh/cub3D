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
#include "stdlib.h"
#include "cub3D.h"

int	hook_keydown(int key, t_data *data)
{
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (move(key, data))
		render(data);
	return (0);
}

/*
 * Useful prototypes to work with mouse
 *
 * int		mlx_mouse_hide();
 * int		mlx_mouse_show();
 * int		mlx_mouse_get_pos(void *win_ptr, int *x, int *y);
 *
 * 	mlx_hook(vars.win, 2, 1L<<6, close, &vars);
 * 	int (*f)(int x, int y, void *param)
*/

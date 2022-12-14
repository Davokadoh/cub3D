/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:15:53 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/14 14:49:26 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "keys.h"
#include "stdlib.h"
#include "cub3D.h"

int	close_hook(int button, t_data *data)
{
	(void)button;
	(void)data;
	exit(0);
	return (0);
}
int	hook_keydown(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(data->mlx, data->view2d.img);
		mlx_destroy_image(data->mlx, data->view3d.img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (move(key, data))
	{
		mlx_destroy_image(data->mlx, data->view2d.img);
		mlx_destroy_image(data->mlx, data->view3d.img);
		mlx_clear_window(data->mlx, data->win);
		render(data);
	}
	if (key == KEY_O || key == KEY_C)
	{
		if (!open_close_door(data, key))
		{
			mlx_destroy_image(data->mlx, data->view2d.img);
			mlx_destroy_image(data->mlx, data->view3d.img);
			mlx_clear_window(data->mlx, data->win);
			render(data);
		}
	}
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

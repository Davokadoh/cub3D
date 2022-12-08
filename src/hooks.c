/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:15:53 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/08 11:25:06 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "keys.h"
#include "stdlib.h"
#include "cub3D.h"

// void	init_win(t_data *data)
// {
// 	// data->mlx = mlx_init();
// 	// if (!data->mlx) //Prevents env -i crash
// 	// 	return (1);
// 	// data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, av[1]);
// 	// if (!data->win)
// 	// 	return (1);
// 	// data->minimap = calculate_minimap(&data);
// 	// mlx_expose_hook(data->win, expose_hook, v);
// 	// mlx_hook(data->win, EVENT_ON_MOUSEMOVE, 64, motion_hook, v);
// 	mlx_hook(data->win, EVENT_ON_DESTROY, 0, close_hook, v);
// 	mlx_hook(data->win, EVENT_ON_KEYDOWN, 0, key_hook, v);
// 	// mlx_hook(data->win, EVENT_ON_MOUSEDOWN, 0, mouse_hook, v);
// 	// mlx_do_key_autorepeaton(data->mlx);
// 	// mlx_loop(data->mlx);
// 	// exit(0);
// }

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
		// mlx_destroy_image(data->mlx, data->view3d.img);
		// mlx_destroy_image(data->mlx, data->minimap.img);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (move(key, data))
	{
		mlx_destroy_image(data->mlx, data->view2d.img);
		// mlx_destroy_image(data->mlx, data->view3d.img);
		// mlx_destroy_image(data->mlx, data->minimap.img);
		mlx_clear_window(data->mlx, data->win);
		render(data);
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

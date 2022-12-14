/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:07 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/14 11:23:37 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3D.h"
#include "keys.h"

static void	hooks(t_data *data)
{
	mlx_mouse_hide(data);
	mlx_mouse_move(data->win, WIN_W / 2, WIN_H / 2);
	mlx_hook(data->win, EVENT_ON_DESTROY, 0, close_hook, data);
	mlx_hook(data->win, EVENT_ON_KEYDOWN, 0, keydown_hook, data);
	mlx_hook(data->win, EVENT_ON_MOUSEMOVE, 0, mouse_hook, data);
	mlx_loop_hook(data->mlx, render, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parse(ac, av, &data))
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx) //Prevents env -i crash
		return (1);
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, av[1]);
	if (!data.win)
		return (1);
	data.minimap = calculate_minimap(&data);
	init_texture(&data); //Change to load_textures
	render(&data);
	hooks(&data);
	mlx_loop(data.mlx);
}

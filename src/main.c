/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:07 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/30 17:34:05 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3D.h"

static void	hooks(t_data *data)
{
	mlx_key_hook(data->win, hook_keydown, &data);
	mlx_mouse_hook(data->win, hook_mousemove, &data);
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
	render(&data);
	hooks(&data);
	mlx_loop(data.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:07 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 15:00:49 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3D.h"

static void	hooks(t_data *data)
{
	mlx_key_hook(data->win, hook_keydown, &data);
	//ToDo: mousehook
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
	data.minimap = calculate_minimap(data);
	if (!data.win)
		return (1);
	render(&data);
	hooks(&data);
	mlx_loop(data.mlx);
}

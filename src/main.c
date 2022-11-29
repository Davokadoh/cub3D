/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:07 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/29 17:32:01 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "cub3D.h"
#include <stdio.h>

static void	test_pixel_put(void *mlx, void *win)
{
	int	i;

	i = -1;
	while (++i < WIN_W)
		mlx_pixel_put(mlx, win, i, 11, 0xFFFFFF);
	i = -1;
	while (++i < WIN_W)
		mlx_pixel_put(mlx, win, i, WIN_H - 11, 0xFFFFFF);
	i = -1;
	while (++i < WIN_H)
		mlx_pixel_put(mlx, win, 11, i, 0xFFFFFF);
	i = -1;
	while (++i < WIN_H)
		mlx_pixel_put(mlx, win, WIN_W - 11, i, 0xFFFFFF);
}

/*
static int	parse(char *file_name, t_map map, char *textures_paths[6])
{
	int	fd;

	if (argc != 2)
	{
		//print_error("Usage: ./miniRT path_to_scene");
		return (-1);
	}
	//check if file ext is .cub
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = gnl(fd)) != NULL)
	{
		if (strncmp("NO")
			textures_paths[0] = ft_split(line, ' ')[1];
		if (strncmp("SO")
			textures_paths[1] = ft_split(line, ' ')[1];
		if (strncmp("WE")
			textures_paths[2] = ft_split(line, ' ')[1];
		if (strncmp("EA")
			textures_paths[3] = ft_split(line, ' ')[1];
		if (strncmp("F")
			textures_paths[4] = ft_split(line, ' ')[1];
		if (strncmp("C")
			textures_paths[5] = ft_split(line, ' ')[1];
	}
	return (0);
}
*/

static char	**get_map()
{
	char	**map 		=  {"111111111",
							"100000001",
							"100000001",
							"100000001",
							"1000N0001",
							"100000001",
							"100000001",
							"100000001",
							"100000001",
							"111111111"};
	return (map);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	void	*img;
	char	**map;
	char	*textures_paths[6];

	//if (parse(init(argc, argv), map, textures_paths))
	//	return (1);
	map = get_map();
	mlx = mlx_init();
	if (!mlx) //Prevent env -i crash
		return (1);
	win = mlx_new_window(mlx, WIN_W, WIN_H, argv[1]);
	img = mlx_new_image(mlx, WIN_W, WIN_H);
	//mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
	//mlx_destroy_image(void *mlx_ptr, void *img_ptr);
	test_pixel_put(mlx, win);
    mlx_loop(mlx);
	printf("test\n");
}

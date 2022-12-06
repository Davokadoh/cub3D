/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:23:40 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 13:52:39 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3D.h"

static int	check_extension(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		return (put_error("Wrong file extension, need .cub", 2));
	else if (ft_strncmp(ext, ".cub", 3))
		return (put_error("Wrong file extension, need .cub", 2));
	return (0);
}

int	parse(int ac, char **av, t_data *data)
{
	size_t	map_start;

	if (ac != 2)
		return (put_error("Usage: cub3D path_to_file", 1));
	if (check_extension(av[1]))
		return (2);
	map_start = get_map_start(av[1]);
	if (get_textures(av[1], data->textures, map_start) > 0) //Need to pass map_start
		return (put_error("Can't get textures", 4));
<<<<<<< HEAD
	/*
	if (get_map(av[1], data->map) > 0) //Need to pass map_start
		return (put_error("Can't get map", 5));
	if (get_camera(data) > 0) 
		return (put_error("Can't get camera", 6)); //Need to pass map_start
	*/
=======
	*/
	if (get_map(fd, &data->map) > 0)
		return (put_error("Can't get map", 5));
	printf("BYE\n");
	if (get_camera(data) > 0)
		return (put_error("Can't get camera", 6));
>>>>>>> 1eb0c13e325230e74e942f8347900d70df6a8195
	return (0);
}


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

//Doesn't check if multiple instance on same line
static int	get_camera_in_line(char *line)
{
	if (ft_strchr(line, 'N'))
		return (1);
	else if (ft_strchr(line, 'S'))
		return (1);
	else if (ft_strchr(line, 'E'))
		return (1);
	else if (ft_strchr(line, 'W'))
		return (1);
	else
		return (0);
}
static int	check_unique_camera(char **map)
{
	int		i;
	int		camera;
	int		new_camera;

	camera = 0;
	i = -1;
	while (map[++i] != NULL)
	{
		new_camera = get_camera_in_line(map[i]);
		if (camera && new_camera)
			return (1);
		camera = new_camera;
	}
	return (camera);
}

//Doesn't add camera pos to data
//Doesn't add camera dir to data
static int	get_camera(t_data *data)
{
	if (check_unique_camera(data->map))
		return (put_error("There is more than one camera", 7));
	return (0);
}

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
	int	fd;

	if (ac != 2)
		return (put_error("Usage: cub3D path_to_file", 1));
	if (check_extension(av[1]))
		return (2);
	if ((fd = open(av[1], O_RDONLY)) < 0) //Need to close fd when finished reading
		return (put_error("Can't open file", 3));
	/*
	if (get_textures(fd, data->textures) > 0)
		return (put_error("Can't get textures", 4));
	*/
	if (get_map(fd, &data->map) > 0)
		return (put_error("Can't get map", 5));
	printf("BYE\n");
	if (get_camera(data) > 0)
		return (put_error("Can't get camera", 6));
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:23:40 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/30 17:34:02 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3D.h"
	
typedef struct	s_map
{
	int	start;
	int end;
}				t_map;

static t_map	get_map_start(char *file_path)
{
	char	*line;
	int		fd;
	t_map	res;

	res.start = 0;
	res.end = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		put_error("Can't open file", -1);
		return (res);
	}
	res.end = 0;
	line = get_next_line(fd);
	res.start = 0;
	while (line != NULL)
	{
		if (*line == '\n')
			res.start = res.end;
		line = get_next_line(fd);
		res.end++;
	}
	close(fd);
	return (res);
}

static int	check_file_extension(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		return (put_error("Wrong file extension, need .cub", 2));
	else if (ft_strncmp(ext, ".cub", 3))
		return (put_error("Wrong file extension, need .cub", 2));
	return (0);
}
/*
static void	print_map(t_data *data)
{
	int i = 0 -1;

	while (data->map[++i])
		printf("%s\n", data->map[i]);
}
*/

int	parse(int ac, char **av, t_data *data)
{
	t_map	map;

	if (ac != 2)
		return (put_error("Usage: cub3D path_to_file", 1));
	if (check_file_extension(av[1]))
		return (2);
	map = get_map_start(av[1]);
	if (get_textures(av[1], map.start, data->textures) > 0)
		return (put_error("Can't get textures", 4));
	if (get_map(av[1], map.start, map.end, &data->map) > 0)
		return (put_error("Can't get map", 5));
	//print_map(data);
	if (get_camera(data) > 0) 
		return (put_error("Can't get camera", 6));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:23:40 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 18:08:00 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_map
{
	int	start;
	int	end;
}				t_map;

static t_map	get_map_start(int fd)
{
	char	*line;
	t_map	res;

	res.start = 0;
	res.end = 0;
	line = get_next_line(fd);
	res.start = 0;
	while (line != NULL)
	{
		if (*line == '\n')
			res.start = res.end;
		free(line);
		line = get_next_line(fd);
		res.end++;
	}
	close(fd);
	return (res);
}

static int	check_file_extension(char *str, char *extension)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		return (printf("%s need an extension %s\n", str, extension));
	else if (ft_strncmp(ext, extension, 3))
		return (printf("%s need the extension %s\n", str, extension));
	return (0);
}

static int	check_textures(char *paths[])
{
	int	i;
	int	fd;

	i = 2;
	while (i < 7)
	{
		if (paths[i])
		{
			if (check_file_extension(paths[i], ".xpm"))
				return (1);
			fd = open(paths[i], O_RDONLY);
			if (fd < 0)
				return (1);
			close(fd);
		}
		i++;
	}
	return (0);
}

int	parse(int ac, char **av, t_data *data)
{
	t_map	map;
	int		fd;

	if (ac != 2)
		return (put_error(NULL, "Usage: cub3D path_to_file", 1));
	if (check_file_extension(av[1], ".cub"))
		return (put_error(data, "Can't open file", 1));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (put_error(data, "Can't open file", 1));
	map = get_map_start(fd);
	if (map.end - map.start < 4)
		return (put_error(data, "Can't get map", 5));
	if (get_paths(av[1], map.start, data->paths) > 0)
		return (put_error(data, "Can't get textures", 4));
	if (check_textures(data->paths) > 0)
		return (put_error(data, "Can't open textures", 4));
	if (check_colors(data) > 0)
		return (put_error(data, "Ceilling or/and floor wrong declared", 4));
	if (get_map(av[1], map.start, map.end, data) > 0)
		return (put_error(data, "Can't get map", 5));
	if (get_player(data) > 0)
		return (put_error(data, "Can't get player", 6));
	return (0);
}

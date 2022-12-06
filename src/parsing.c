/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:23:40 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 14:09:55 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3D.h"

typedef struct s_map
{
	int	start;
	int	end;
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
	if (get_player(data) > 0)
		return (put_error("Can't get playerera", 6));
	printf("pos: x:%f, y:%f\n", data->player.pos.x, data->player.pos.y);
	printf("dir: x:%f, y:%f\n", data->player.dir.x, data->player.dir.y);
	return (0);
}


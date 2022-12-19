/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:23:40 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/19 15:00:50 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

int	check_textures(char *t_path[])
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		if (check_file_extension(t_path[i], ".xpm"))
			return (1);
		fd = open(t_path[i], O_RDONLY);
		if (fd < 0)
			return (1);
		close(fd);
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
	if (get_textures(av[1], map.start, data->t_path) > 0)
		return (put_error(data, "Can't get textures", 4));
	if (check_textures(data->t_path) > 0)
		return (put_error(data, "Can't open textures", 4));
	if (check_colors(data) > 0)
		return (put_error(data, "Ceilling or/and floor wrong declared", 4));
	if (get_map(av[1], map.start, map.end, &data->map) > 0)
		return (put_error(data, "Can't get map", 5));
	if (get_player(data) > 0)
		return (put_error(data, "Can't get player", 6));
	return (0);
}

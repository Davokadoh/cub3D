/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:37 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 14:56:51 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	textures_init(char *paths[10])
{
	int	i;

	i = -1;
	while (++i < 10)
		paths[i] = NULL;
}

static int	get_texture_index(char *line)
{
	if (!ft_strncmp("NO", line, 2))
		return (2);
	else if (!ft_strncmp("EA", line, 2))
		return (3);
	else if (!ft_strncmp("SO", line, 2))
		return (4);
	else if (!ft_strncmp("WE", line, 2))
		return (5);
	else if (!ft_strncmp("F", line, 1))
		return (0);
	else if (!ft_strncmp("C", line, 1))
		return (1);
	else if (!ft_strncmp("D", line, 1))
		return (6);
	else if (!ft_strncmp("P", line, 1))
		return (7);
	else if (!ft_strncmp("A", line, 1))
		return (8);
	else
		return (9);
}

static int	add_path(char *line, char *paths[10])
{
	char	**splited;
	int		index;

	if (*line == '\n')
		return (0);
	splited = ft_split(line, ' ');
	index = get_texture_index(splited[0]);
	if (splited[1])
	{
		if (paths[index])
			return (printf("A texture is defined twice\n"));
		paths[index] = ft_strdup(splited[1]);
		paths[index][ft_strlen(paths[index]) - 1] = '\0';
	}
	ft_free_tab(splited);
	return (0);
}

int	free_textures(char *paths[10])
{
	int	i;

	i = -1;
	while (++i < 9)
	{
		ft_free(paths[i]);
	}
	return (1);
}

int	get_paths(char *file_path, size_t map_start, char *paths[10])
{
	char	*line;
	size_t	line_nbr;
	int		fd;

	line_nbr = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (printf("Can't open file\n"));
	line = get_next_line(fd);
	while (line != NULL && line_nbr < map_start)
	{
		if (add_path(line, paths))
			return (1);
		free(line);
		line = get_next_line(fd);
		line_nbr++;
	}
	free(line);
	if (!paths[0] || !paths[1] || !paths[2] || !paths[3]
		|| !paths[4] || !paths[5])
		paths[9] = "1";
	close(fd);
	return (paths[9] != NULL);
}

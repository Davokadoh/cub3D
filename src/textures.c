/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:37 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/12 17:35:24 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

static void	textures_init(char *t_path[7])
{
	int	i;

	i = -1;
	while (++i < 7)
		t_path[i] = NULL;
}

static int	get_texture_index(char *line)
{
	if (!ft_strncmp("NO", line, 2))
		return (0);
	else if (!ft_strncmp("SO", line, 2))
		return (1);
	else if (!ft_strncmp("WE", line, 2))
		return (2);
	else if (!ft_strncmp("EA", line, 2))
		return (3);
	else if (!ft_strncmp("F", line, 1))
		return (4);
	else if (!ft_strncmp("C", line, 1))
		return (5);
	else
		return (6);
}

static int	add_path(char *line, char *t_path[7])
{
	char	**splited;
	int		index;

	if (*line == '\n')
		return (0);
	splited = ft_split(line, ' ');
	index = get_texture_index(splited[0]);
	if (splited[1])
	{
		t_path[index] = ft_strdup(splited[1]);
		t_path[index][ft_strlen(t_path[index]) - 1] = '\0';
	}
	ft_free_tab(splited);
	return (0);
}

static int	free_textures(char *t_path[7])
{
	int	i;

	i = -1;
	while (++i < 7)
		free(t_path[i]);
	free(t_path);
	return (1);
}

int	get_textures(char *file_path, size_t map_start, char *t_path[7])
{
	char	*line;
	size_t	line_nbr;
	int		fd;

	textures_init(t_path);
	line_nbr = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (put_error("Can't open file", 1));
	line = get_next_line(fd);
	while (line != NULL && line_nbr < map_start)
	{
		if (add_path(line, t_path))
			return (free_textures(t_path));
		free(line);
		line = get_next_line(fd);
		line_nbr++;
	}
	free(line);
	if (!t_path[0] || !t_path[1] || !t_path[2] || !t_path[3]
		|| !t_path[4] || !t_path[5])
		t_path[6] = "1";
	close(fd);
	return (t_path[6] != NULL);
}

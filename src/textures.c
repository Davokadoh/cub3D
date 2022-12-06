/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:07:37 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/30 17:09:38 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	textures_init(char *textures[7])
{
	int	i;

	i = -1;
	while (textures[++i])
		textures[i] = NULL;
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

static int	add_path(char *line, char *textures[7])
{
	char	**splited;
	int		index;

	if (*line == '\n')
		return (0);
	splited = ft_split(line, ' ');
	index = get_texture_index(splited[0]);
	if (splited[1])
	{
		textures[index] = ft_strdup(splited[1]); //Copies \n too
		textures[index][ft_strlen(textures[index]) - 1] = '\0';
	}
	ft_free_tab(splited);
	return (0);
}

static void	print_textures(char *textures[7])
{
	int	path;

	path = -1;
	while (textures[++path])
		printf("textures[%i] = %s\n", path, textures[path]);
}

static int	free_textures(char *textures[7])
{
	int	i;

	i = -1;
	while (++i < 7)
		free(textures[i]);
	free(textures);
	return (1);
}

int	get_textures(char *file_path, size_t map_start, char *textures[7])
{
	char	*line;
	size_t	line_nbr;
	int		fd;

	textures_init(textures);
	line_nbr = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (put_error("Can't open file", 1));
	line = get_next_line(fd);
	while (line != NULL && line_nbr < map_start)
	{
		if (add_path(line, textures))
			return (free_textures(textures));
		line = get_next_line(fd);
		line_nbr++;
	}
	if (!textures[0] || !textures[1] || !textures[2] || !textures[3]
		|| !textures[4] || !textures[5])
		textures[6] = "1";
	print_textures(textures);
	printf("textures[6] = %s\n\n", textures[6]);
	return (textures[6] != NULL);
}

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

#include "libft.h"
#include "cub3D.h"

static int	get_texture_index(char *line)
{
	if (ft_strncmp("NO", line, 2))
		return (0);
	else if (ft_strncmp("SO", line, 2))
		return (1);
	else if (ft_strncmp("WE", line, 2))
		return (2);
	else if (ft_strncmp("EA", line, 2))
		return (3);
	else if (ft_strncmp("F", line, 1))
		return (4);
	else if (ft_strncmp("C", line, 1))
		return (5);
	else
		return (6);
}

static int	add_path(char *line, char *textures[7])
{
	char	**splited;
	int		index;

	printf("A\n");
	splited = ft_split(line, ' ');
	printf("B\n");
	index = get_texture_index(splited[0]);
	printf("C\n");
	textures[index] = ft_strdup(splited[1]);
	printf("D\n");
	ft_free_tab(splited);
	return (0);
}

static void	textures_init(char *textures[7])
{
	int	i;

	i = -1;
	while (textures[++i])
		textures[i] = NULL;
	textures[6] = "1";
}

static int	is_map_char(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '0')
		return (1);
	else if (c == '1')
		return (1);
	else if (c == 'N')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == 'E')
		return (1);
	else if (c == 'W')
		return (1);
	else
		return (0);
}

static int	is_map(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!is_map_char(line[i]))
		{
			printf("'Not map char': '%c'\n", line[i]);
			return (0);
		}
	return (1);
}

//Need to stop when we get to map
int	get_textures(int fd, char *textures[7])
{
	char	*line;

	textures_init(textures);
	line = get_next_line(fd);
	while (line != NULL && !is_map(line))
	{
		printf("%s\n", line);
		if (*line != '\n')
			if (add_path(line, textures))
				return (1);
		line = get_next_line(fd); //Need to add to project
	}
	int i = -1;
	while (textures[++i])
		printf("textures[%i] = %s\n", i, textures[i]);
	if (!textures[0] || !textures[1] || !textures[2] || !textures[3]\
			|| !textures[4] || !textures[5])
		textures[6] = NULL;
	printf("textures[6] = %s\n", textures[6]);
	return (textures[6] == NULL);
}

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

static int	get_texture_index(char *line)
{
	if (ft_strncmp("NO", line))
		return (0);
	else if (ft_strncmp("SO", line))
		return (1);
	else if (ft_strncmp("WE", line))
		return (2);
	else if (ft_strncmp("EA", line))
		return (3);
	else if (ft_strncmp("F", line))
		return (4);
	else if (ft_strncmp("C", line))
		return (5);
	else
		return (6);
}

static int	add_textures(char *line, char *textures[7])
{
	char	**splited;
	int		index;

	splited = ft_split(line, ' ');
	index = get_texture_index(splited[0]);
	textures[index] = splited[1];
}

static void	textures_init(char *textures[7])
{
	int	i;

	i = -1;
	while (textures[++i])
		textures[i] = NULL;
}

//Need to stop when we get to map
int	get_textures(int fd, char *textures[7])
{
	textures_init(textures); //Set all to NULL, important for index 6
	line = gnl(fd);
	while (line != NULL && is_not_map())
	{
		if (is_only_whitespaces(line))
			continue ;
		add_texture(line, textures);
		line = get_next_line(fd); //Need to add to project
	}
	if (!textures[0] || !textures[1] || !textures[2] || !textures[3]\
			|| !textures[4] || !textures[5])
		textures[6] = 1;
	return (textures[6]);
}

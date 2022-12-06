#include "libft.h"
#include "cub3D.h"

//Doesn't check if multiple instance on same line
static int	get_camera_in_line(char *line)
{
	if (ft_strchr(line, 'N'))
		return (1);
	else if (ft_strchr(line, 'S'))
		return (1);
	else if (ft_strchr(line, 'W'))
		return (1);
	else if (ft_strchr(line, 'E'))
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

static t_vec2d	new_vec(float x, float y)
{
	t_vec2d	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

static t_vec2d	get_pos(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				return (new_vec(j, i));
		}
	}
	return (new_vec(i, j));
}

static t_vec2d	get_dir(char c)
{
	t_vec2d dir;

	if (c == 'N')
		dir = new_vec(0, -1);
	else if (c == 'S')
		dir = new_vec(0, 1);
	else if (c == 'W')
		dir = new_vec(-1, 0);
	else if (c == 'E')
		dir = new_vec(1, 0);
	else
		dir = new_vec(0, 0);
	return (dir);
}

int	get_camera(t_data *data)
{
	t_vec2d	pos;

	if (check_unique_camera(data->map))
		return (put_error("", 7));
	pos = get_pos(data->map);
	data->cam.pos = pos;
	data->cam.dir = get_dir(data->map[(int)floor(pos.y)][(int)floor(pos.x)]);
	return (0);
}

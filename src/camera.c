#include "libft.h"
#include "cub3D.h"

//Doesn't check if multiple instance on same line
static int	get_camera_in_line(char *line)
{
	if (ft_strchr(line, 'N'))
		return (1);
	else if (ft_strchr(line, 'S'))
		return (1);
	else if (ft_strchr(line, 'E'))
		return (1);
	else if (ft_strchr(line, 'W'))
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

//Doesn't add camera pos to data
//Doesn't add camera dir to data
int	get_camera(t_data *data)
{
	if (check_unique_camera(data->map))
		return (put_error("There is more than one camera", 7));
	return (0);
}

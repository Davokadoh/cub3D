#include "cub3D.h"
#include "keys.h"

int	move_forward(t_data *data)
{
	data->cam.pos.x += 0.1 * data->cam.dir.x;
	data->cam.pos.y += 0.1 * data->cam.dir.y;
	return (1);
}

int	move_backward(t_data *data)
{
	data->cam.pos.x -= 0.1 * data->cam.dir.x;
	data->cam.pos.y -= 0.1 * data->cam.dir.y;
	return (1);
}

int	move_left(t_data *data)
{
	data->cam.pos.x += 0.1 * data->cam.dir.x;
	data->cam.pos.y += 0.1 * data->cam.dir.y;
	return (1);
}

int	move_right(t_data *data)
{
	data->cam.pos.x += 0.1 * data->cam.dir.x;
	data->cam.pos.y += 0.1 * data->cam.dir.y;
	return (1);
}

int	turn_left(t_data *data)
{
	data->cam.dir.x += 0.1 * data->cam.dir.x;
	data->cam.dir.y += 0.1 * data->cam.dir.y;
	return (1);
}

int	turn_right(t_data *data)
{
	data->cam.dir.x -= 0.1 * data->cam.dir.x;
	data->cam.dir.y -= 0.1 * data->cam.dir.y;
	return (1);
}

int	move(int key, t_data *data) //bool ?
{
	if (key == KEY_W)
		return (move_forward(data));
	else if (key == KEY_A)
		return (move_left(data));
	else if (key == KEY_S)
		return (move_backward(data));
	else if (key == KEY_D)
		return (move_right(data));
	else if (key == KEY_Q || key == KEY_LEFT)
		return (turn_left(data));
	else if (key == KEY_E || key == KEY_RIGHT)
		return (turn_right(data));
	return (0);
}

#include "cub3D.h"

void	drawfloorceiling(t_img *img, char *t_path[7])
{
	int	x;
	int	y;
	int	colorf;
	int colorc;

	x = -1;
	y = -1;
	colorf = str_to_rgb_int(t_path[4]);
	colorc = str_to_rgb_int(t_path[5]);
	while (++y <= WIN_H / 2)
	{
		while (++x <=WIN_W)
			put_pixel_img(img, x, y, colorc);
		x = -1;
	}
	while (++y <= WIN_H)
	{
		while (++x <=WIN_W)
			put_pixel_img(img, x, y, colorf);
		x = -1;
	}
}

int	get_texel_x(t_data *data, t_cam ray)
{
	t_img	texture;
	int		orientation;
	int		x;
	char	c;

	orientation = compass(ray);
	c = data->map[(int)ray.pos.y][(int)ray.pos.x];
	texture = data->textures[orientation - 1];
	if (c == 'D')
		texture = data->textures[4];
	if (orientation == 1)
		x = (int)(fmod(ray.pos.x, 1.0) * texture.w);
	if (orientation == 2)
		x = (int)(fmod(ray.pos.y, 1.0) * texture.w);
	if (orientation == 3)
		x = (int)((1 - fmod(ray.pos.x, 1.0)) * texture.w);
	if (orientation == 4)
		x = (int)((1 - fmod(ray.pos.y, 1.0)) * texture.w);
	return (x);
}

int	get_texel_y(t_img texture, float img_y, float wall_top, float line_height)
{
	int		y;

	y = (img_y - wall_top) * texture.h * 0.25 / line_height;
	return ((int)y);
}

unsigned int	get_texel(t_img texture, int x, int y)
{
	unsigned int	clr;

	clr = *(unsigned int*)(texture.addr + (y * texture.line_size + x) * (texture.bits_per_pixel / 8));
	return (clr);
}

void	draw3d(t_data *data, t_cam rays[WIN_W])
{
	float	wall_bot;
	float	wall_top;
	float	line_height;
	t_vec2d	texel;
	t_img	texture;
	int		x;
	char	c;

	x = -1;
	while (++x < WIN_W)
	{
		c = data->map[(int)rays[x].pos.y][(int)rays[x].pos.x];
		line_height = (WIN_H / rays[x].dist);
		texture = data->textures[compass(rays[x]) - 1];
		if (c == 'D')
			texture = data->textures[4];
		texel.x = get_texel_x(data, rays[x]);
		wall_top = -line_height / 2 + WIN_H / 2;
		wall_bot = line_height / 2 + WIN_H / 2;
		while (--wall_bot > wall_top)
		{
			texel.y = get_texel_y(texture, wall_bot, wall_top, line_height);
			put_pixel_img(&data->view3d, x, (int)wall_bot, get_texel(texture, (int)texel.x, (int)texel.y));
		}
	}
}

int	init_texture(t_data *data)
{
	data->textures[0].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[0], &data->textures[0].h, &data->textures[0].w);
	if (data->textures[0].img == NULL)
		return (put_error(data, "texture error", 7));
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img, &data->textures[0].bits_per_pixel,
			&data->textures[0].line_size, &data->textures[0].endian);
	data->textures[1].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[1], &data->textures[1].h, &data->textures[1].w);
	if (data->textures[1].img == NULL)
		return (put_error(data, "texture error", 7));
	data->textures[1].addr = mlx_get_data_addr(data->textures[1].img, &data->textures[1].bits_per_pixel,
			&data->textures[1].line_size, &data->textures[1].endian);
	data->textures[2].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[2], &data->textures[2].h, &data->textures[2].w);
	if (data->textures[2].img == NULL)
		return (put_error(data, "texture error", 7));
	data->textures[2].addr = mlx_get_data_addr(data->textures[2].img, &data->textures[2].bits_per_pixel,
			&data->textures[2].line_size, &data->textures[2].endian);
	data->textures[3].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[3], &data->textures[3].h, &data->textures[3].w);
	if (data->textures[3].img == NULL)
		return (put_error(data, "texture error", 7));
	data->textures[3].addr = mlx_get_data_addr(data->textures[3].img, &data->textures[3].bits_per_pixel,
			&data->textures[3].line_size, &data->textures[3].endian);
	data->textures[4].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bois.xpm", &data->textures[4].h, &data->textures[4].w);
	if (data->textures[4].img == NULL)
		return (put_error(data, "texture error", 7));
	data->textures[4].addr = mlx_get_data_addr(data->textures[4].img, &data->textures[4].bits_per_pixel,
			&data->textures[4].line_size, &data->textures[4].endian);
	return (0);
}

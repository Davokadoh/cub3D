#include "cub3D.h"

void	drawfloorceiling(t_img *img)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y <= WIN_H / 2)
	{
		while (++x <=WIN_W)
			put_pixel_img(img, x, y, 0x00333333);
		x = -1;
	}
	while (++y <= WIN_H)
	{
		while (++x <=WIN_W)
			put_pixel_img(img, x, y, 0x00954242);
		x = -1;
	}
}

int	find_x_text(t_data *data, t_cam ray)
{
	t_img	texture;
	int		orientation;
	int		x;

	orientation = compass(ray);
	texture = data->textures[orientation - 1];
	if (orientation == 1)
	{
		x = (int)(fmod(ray.pos.x, 1.0) * texture.w);
	}
	if (orientation == 2)
	{
		x = (int)(fmod(ray.pos.y, 1.0) * texture.w);
	}
	if (orientation == 3)
	{
		x = (int)((1 - fmod(ray.pos.x, 1.0)) * texture.w);
	}
	if (orientation == 4)
	{
		x = (int)((1 - fmod(ray.pos.y, 1.0)) * texture.w);
	}
	return (x);
}

int	find_y_text(t_img texture, float img_y, float wall_top, float line_height)
{
	int		y;

	y = (img_y - wall_top) * texture.h * 0.25 / line_height;
	return ((int)y);
}

unsigned int	get_color_tex(t_img texture, t_vec2d texture_pos)
{
	unsigned int	clr;
	int				t;
	int				r;
	int				g;
	int				b;

	clr = *(unsigned int*)(texture.addr + (((int)texture_pos.y * texture.line_size + (int)texture_pos.x) * (texture.bits_per_pixel / 8)));
	t = ((clr >> 24) & 0xFF);
	r = ((clr >> 16) & 0xFF);
	g = ((clr >> 8) & 0xFF);
	b = (clr & 0xFF);
	return (((t & 0xFF) << 24) + ((r & 0xFF) << 16)
		+ ((g & 0xFF) << 8) + (b & 0xFF));
}

void	draw3d_text(t_data *data, double dist, int x, t_cam ray) //need to explain name for rad_ang, why not current_angle or something else ?
{
	float	wall_bot;
	float	wall_top;
	float	line_height;
	t_vec2d	texture_pos;
	t_img	texture;

	line_height = (WIN_H / dist);
	texture = data->textures[compass(ray) - 1];
	texture_pos.x = find_x_text(data, ray);
	wall_top = -line_height / 2 + WIN_H / 2;
	// if (wall_top < 0)
	// 	wall_top = 0;
	wall_bot = line_height / 2 + WIN_H / 2;
	// if (wall_bot >= WIN_H)
	// 	wall_bot = WIN_H - 1;
	while (--wall_bot > wall_top)
	{
		texture_pos.y = find_y_text(texture, wall_bot, wall_top, line_height);
		// printf("y = %f, texture_h %d\n", texture_pos.y, texture.h);
		// printf("color: %u\n",get_color_tex(texture, texture_pos));
		put_pixel_img(&data->view3d, x, (int)wall_bot, get_color_tex(texture, texture_pos));
	}
}

int	init_texture(t_data *data)
{
	data->textures[0].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[0], &data->textures[0].h, &data->textures[0].w);
	if (data->textures[0].img == NULL)
		return (put_error("texture error", 7));
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img, &data->textures[0].bits_per_pixel,
			&data->textures[0].line_size, &data->textures[0].endian);
	data->textures[1].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[1], &data->textures[1].h, &data->textures[1].w);
	if (data->textures[1].img == NULL)
		return (put_error("texture error", 7));
	data->textures[1].addr = mlx_get_data_addr(data->textures[1].img, &data->textures[1].bits_per_pixel,
			&data->textures[1].line_size, &data->textures[1].endian);
	data->textures[2].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[2], &data->textures[2].h, &data->textures[2].w);
	if (data->textures[2].img == NULL)
		return (put_error("texture error", 7));
	data->textures[2].addr = mlx_get_data_addr(data->textures[2].img, &data->textures[2].bits_per_pixel,
			&data->textures[2].line_size, &data->textures[2].endian);
	data->textures[3].img = mlx_xpm_file_to_image(data->mlx,
			data->t_path[3], &data->textures[3].h, &data->textures[3].w);
	if (data->textures[3].img == NULL)
		return (put_error("texture error", 7));
	data->textures[3].addr = mlx_get_data_addr(data->textures[3].img, &data->textures[3].bits_per_pixel,
			&data->textures[3].line_size, &data->textures[3].endian);
	printf(" texture 1 %s, h %d, w %d\n", data->t_path[0], data->textures[0].h, data->textures[0].w);
	printf(" texture 2 %s, h %d, w %d\n", data->t_path[1], data->textures[1].h, data->textures[1].w);
	printf(" texture 3 %s, h %d, w %d\n", data->t_path[2], data->textures[2].h, data->textures[2].w);
	printf(" texture 4 %s, h %d, w %d\n", data->t_path[3], data->textures[3].h, data->textures[3].w);
	printf("img : %p\n", data->textures[0].img);
	printf("addr : %p\n", data->textures[0].addr);
	printf("bbp : %d\n", data->textures[0].bits_per_pixel);
	printf("line_size : %d\n", data->textures[0].line_size);
	printf("endian : %d\n", data->textures[0].endian);
	return (0);
}

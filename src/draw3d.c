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

	if (x > texture.w)
		return (0x00000000); //Change to macro def
	clr = *(unsigned int*)(texture.addr + (y * texture.line_size + x) * (texture.bits_per_pixel / 8));
	return (clr);
}

long	now(int init)
{
	struct timeval		time;
	static long			start = 0;
	long				milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000L + time.tv_usec / 1000;
	if (init)
		start = milliseconds;
	return (milliseconds - start);
}

size_t	update(void)
{
	static long last_frame = 0;

	if (now(0) - last_frame > 1)
	{
		last_frame = now(0);
		return (1);
	}
	return (0);
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
	static int	frame = 0;
	int		color;

	x = -1;
	frame += 1 * update();
	frame %= data->textures[2].w + 1;
	while (++x < WIN_W)
	{
		c = data->map[(int)rays[x].pos.y][(int)rays[x].pos.x];
		line_height = (WIN_H / rays[x].dist);
		texture = data->textures[compass(rays[x]) - 1];
		texel.x = get_texel_x(data, rays[x]);
		if (c == 'c') //'c' == closing_door
		{
			texel.x += frame;
			if (frame >= texture.w)
			{
				frame = texture.w;
				data->map[(int)rays[x].pos.y][(int)rays[x].pos.x] = 'd'; //Fully opened now
			}
		}
		else if (c == 'o') //'o' == opening_door
		{
			texel.x -= frame;
			if (frame <= 0)
			{
				frame = 0;
				data->map[(int)rays[x].pos.y][(int)rays[x].pos.x] = 'D'; //Fully opened now
			}
		}
		wall_top = -line_height / 2 + WIN_H / 2;
		wall_bot = line_height / 2 + WIN_H / 2;
		while (--wall_bot > wall_top)
		{
			texel.y = get_texel_y(texture, wall_bot, wall_top, line_height);
			color = get_texel(texture, (int)texel.x, (int)texel.y);
			if (color == 0xFF000000) //Should check if t > 0 but now just PoC
			{
				new_ray = init_ray(ray, ray.angle);
				check_wall(new_ray); //Advance one step otherwise same result as old ray
				new_ray.dist = cast_ray(new_ray);
				draw3d_slice(data, new_ray);
			}
			put_pixel_img(&data->view3d, x, (int)wall_bot, color);
		}
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
	data->textures[4].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/bois.xpm", &data->textures[4].h, &data->textures[4].w);
	if (data->textures[4].img == NULL)
		return (put_error("texture error", 7));
	data->textures[4].addr = mlx_get_data_addr(data->textures[4].img, &data->textures[4].bits_per_pixel,
			&data->textures[4].line_size, &data->textures[4].endian);
	return (0);
}

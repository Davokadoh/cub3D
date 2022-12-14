/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:26 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/14 14:51:05 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stddef.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define WIN_W 1920
# define WIN_H 1080
# define MM_W 300
# define MM_H 200
# define DR (M_PI / 180)
# define FOV (M_PI / 5)

typedef struct	s_vec2d
{
	double	x;
	double	y;
}				t_vec2d;

typedef struct	s_cam
{
	t_vec2d	pos; //Position vector
	t_vec2d	dir; //Looking direction verctor
	double	angle;
	int		c;
}				t_cam;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		h;
	int		w;
}				t_img;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	size_t	map_w;
	size_t	map_h;
	char	*t_path[7];
	t_cam	player;
	t_img	minimap;
	t_img	view2d;
	t_img	view3d;
	t_img	textures[4];
}				t_data;

//Main logic
int		move(int key, t_data *data); //bool
void	render(t_data *data);
void	put_pixel_img(t_img *img, int x, int y, int color);
// double	raycasting(t_cam player, t_data map);
//void	cast_rays();
//void	draw_walls();

//Move and turn
int		turn_left(t_data *data);
int		turn_right(t_data *data);
int		move_forward(t_data *data);
int		move_backward(t_data *data);
int		move_left(t_data *data);
int		move_right(t_data *data);
int		open_close_door(t_data *data, int key);

//Minimap
t_img	calculate_minimap(t_data *data);
int		wall_size(t_data *map);
void	init_img(t_img *img, int width, int height);
void	draw_minimap(t_data *map, t_img *minimap);

//Raycasting
int		ray_dir(t_cam ray);
double	dist_next_h(t_cam ray, int ray_dir);
double	dist_next_v(t_cam ray, int ray_dir);
int		update_rayh(char **map, t_cam *ray, int ray_dir, double dist_h);
int		update_rayv(char **map, t_cam *ray, int ray_dir, double dist_v);
t_cam	init_ray(t_cam player, double radius_angle);
int		check_wall(char **map, t_cam *ray, int ray_dir);
double	ray_dist_draw(char **map, t_cam const player, double rad_ang, t_img *img);
void	view_field(t_data *data, double rad_tot);
int	compass(t_cam ray);

//?????????
void	drawfloorceiling(t_img *img, char *t_path[7]);
// void	draw3d(t_img *img, double dist, int x, int orientation);
void	draw3d_text(t_data *data, double dist, int x, t_cam ray);
int	init_texture(t_data *data);

//Parsing
int		parse(int ac, char **av, t_data *data);
int		get_textures(char *file_path, size_t map_start, char *t_path[7]);
int		get_map(char *file_path, size_t map_start, size_t map_end, char ***map);
int		get_player(t_data *data);

//Utils
t_vec2d	new_vec(double x, double y);
int		put_error(char *err_msg, int err_code);
char	*get_next_line(int fd);

//MLX
void	draw_line(t_vec2d a, t_vec2d b, int color, t_data *data);
int		rgb_to_int(int r, int g, int b);
int		str_to_rgb_int(char * str_rgb);
int		hook_keydown(int key, t_data *data);
int		close_hook(int button, t_data *data);
int		key_hook(int keycode, t_data *data);

#endif

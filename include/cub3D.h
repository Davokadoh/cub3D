/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:26 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/21 14:52:18 by vhaefeli         ###   ########.fr       */
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
# define MM_W 400
# define MM_H 300

typedef struct s_vec2d
{
	double	x;
	double	y;
}				t_vec2d;

typedef struct s_wall
{
	float	top;
	float	bot;
	float	line_h;
}				t_wall;

typedef struct s_cam
{
	t_vec2d	pos;
	t_vec2d	dir;
	double	angle;
	double	dist;
	int		axis;
	int		wall_type;
	int		doors;
}				t_cam;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
	int		h;
	int		w;
	int		frame;
}				t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	size_t	map_w;
	size_t	map_h;
	char	*paths[10];
	t_cam	player;
	t_img	minimap;
	t_img	view2d;
	t_img	view3d;
	t_img	view_doors;
	t_img	textures[7];
	int		color_floor;
	int		color_ceiling;
	int		mouse;
}				t_data;

//camera.c - 5 fcts
int		get_player(t_data *data);

//draw3d.c - 5 fcts
void	draw3d(t_data *data, t_img *view, t_cam rays[WIN_W]);

//error.c - 1 fct
int		put_error(t_data *data, char *err_msg, int err_code);

//gnl.c
char	*get_next_line(int fd);

//hooks.c - 3 fcts
int		close_hook(int button, t_data *data);
int		keydown_hook(int key, t_data *data);
int		mouse_hook(int x, int y, t_data *data);

//line.c - 2 fct
int		draw2d(t_data *data, t_cam rays[WIN_W]);

//map_check.c - 3 fcts
int		check_closed_map(char **map, char **paths);

//map.c - 5 fcts
int		get_map(char *f_path, size_t map_start, size_t map_end, t_data *data);

// minimap.c - 3 fcts
int		calculate_minimap(t_data *data);
int		wall_size(t_data *map);
void	draw_minimap(t_data *map, t_img *minimap);

//move.c - 5 fcts
int		move(int key, t_data *data);

//turn.c - 3 fcts
int		turn_left(t_data *data);
int		turn_right(t_data *data);
int		open_close_door(t_data *data, int key);

//parsing.c - 4 ftcs
int		parse(int ac, char **av, t_data *data);

//raycasting1.c - 5 ftcs
int		ray_dir(t_cam ray);
double	dist_next_h(t_cam ray, int ray_dir);
double	dist_next_v(t_cam ray, int ray_dir);
int		update_rayh(char **map, t_cam *ray, int ray_dir, double dist_h);
int		update_rayv(char **map, t_cam *ray, int ray_dir, double dist_v);

// raycasting2.c - 5 fcts
double	ray_dist(char **map, t_cam const player, t_cam *ray, double rad_ang);
int		compass(t_cam ray);
t_cam	*cast_rays(t_data *data, t_cam *rays, int doors);

//render.c - 5 fcts
void	put_pixel_img(t_img *img, int x, int y, int color);
int		fill_img(t_img *img, int color);
int		init_img(void *mlx, t_img *img, int width, int height);
int		render(t_data *data);

//rgb.c - 4 fcts
int		check_colors(t_data *data);
int		str_to_rgb_int(char *str_rgb);

//textures.c - 1 fct
int		init_texture(t_data *data);

//paths.c - 5 fcts
void	textures_init(char *paths[10]);
int		free_textures(char *paths[10]);
int		get_paths(char *file_path, size_t map_start, char *paths[10]);

//vector2d.c - 1 fct
t_vec2d	new_vec(double x, double y);

//anim.c - 1 fct
void	anim(t_data *data, t_img *texture);

#endif

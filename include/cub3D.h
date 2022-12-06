/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:26 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/06 13:30:34 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

# define WIN_W 640
# define WIN_H 360

typedef struct	s_vec2d
{
	float	x;
	float	y;
}				t_vec2d;

typedef struct	s_cam
{
	t_vec2d	pos; //Position vector
	t_vec2d	dir; //Looking direction verctor
}				t_cam;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	char	*textures[7];
	t_cam	cam;
}				t_data;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}				t_img;

//Main logic
int		move(int key, t_data *data); //bool
void	render(t_data *data);
//void	cast_rays();
//void	draw_walls();

//Parsing
int		parse(int ac, char **av, t_data *data);
int		get_textures(char *file_path, size_t map_start, char *textures[7]);
int		get_map(char *file_path, size_t map_start, size_t map_end, char ***map);
int		get_camera(t_data *data);

//Utils
t_vec2d	new_vec(float x, float y);
int		put_error(char *err_msg, int err_code);
char	*get_next_line(int fd);

//MLX
void	put_pixel_img(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_vec2d a, t_vec2d b, int color);
int		rgb_to_int(double r, double g, double b);
int		hook_keydown(int key, t_data *data);

#endif

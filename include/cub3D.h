/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:26 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/05 18:04:21 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stddef.h>
# include <math.h>
# include <stdlib.h>
# include "libft.h"
#include "mlx.h"

# define WIN_W 1280
# define WIN_H 720
# define MM_W 400
# define MM_H 400
# define DR	M_PI / 180

typedef struct	s_cam
{
	float	pos[2]; //Position vector
	float	dir[2]; //Looking direction verctor
}				t_cam;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	size_t	map_w;
	size_t	map_h;
	char	*textures[7];
	t_cam	camera;
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
void	render(t_data *data);
void	put_pixel_img(t_img *img, int x, int y, int color);
// float	raycasting(t_cam player, t_data map);
//void	cast_rays();
//void	draw_walls();

// minimap
void	put_minimap(t_data *map, t_img *minimap);
int	wall_size(t_data *map);
void	ini_img(t_img *img, int width, int height);
void	draw_minimap(t_data *map, t_img *minimap);

//Parsing
int		parse(int ac, char **av, t_data *data);
int		get_textures(int fd, char *textures[7]);
int		get_map(int fd, char ***map);

//Utils
int		put_error(char *err_msg, int err_code);
char	*get_next_line(int fd);

//MLX
int		rgb_to_int(double r, double g, double b);
int		hook_keydown(int key, t_data data);
int		hook_mousemove(int key, t_data data);

#endif

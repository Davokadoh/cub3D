/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:26 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/30 17:19:29 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stddef.h>

# define WIN_W 640
# define WIN_H 360

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
	char	*textures[7];
	t_cam	camera;
}				t_data;

//Main logic
void	render(t_data data);
//void	cast_rays();
//void	draw_walls();

//Parsing
int		parse(int ac, char **av, t_data *data);
int		get_textures(int fd, char *textures[7]);
char	**get_map(int fd, char **map);

//Utils
int		put_error(char *err_msg, int err_code);
int		rgb_to_int(double r, double g, double b);
int		hook_keydown(int key, t_data data);
int		hook_mousemove(int key, t_data data);

#endif

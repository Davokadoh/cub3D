/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:59:26 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/29 12:36:13 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stddef.h>

# define WIN_W 640
# define WIN_H 360

//Main logic

//Parsing
int		parse(int fd, char **map, char *textures_paths[4]);

//Utils
int		rgb_to_int(double r, double g, double b);

//Progress bar

#endif

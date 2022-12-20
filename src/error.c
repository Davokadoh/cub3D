/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:48 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/20 15:34:57 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	put_error(t_data *data, char *err_msg, int err_code)
{
	printf("Error: %s\n", err_msg);
	if (data)
	{
		ft_free_tab(data->map);
		free_textures(data->paths);
	}
	return (err_code);
}

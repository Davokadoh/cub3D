/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:48 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/14 17:56:20 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	put_error(char *err_msg, int err_code)
{
	printf("Error: %s\n", err_msg);
	return (err_code);
}

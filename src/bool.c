/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:29:55 by jleroux           #+#    #+#             */
/*   Updated: 2022/12/15 14:29:57 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	is_dir(char *path)
{
	bool	res;
	int		fd;

	res = true;
	fd = open(path, O_DIRECTORY, O_RDONLY);
	if (fd < 0)
		res = false;
	close(fd);
	return (res);
}

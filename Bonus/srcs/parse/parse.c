/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:42:35 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 16:05:45 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int	parse_permisions(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			return (print_error(3, file));
		if (errno == EACCES)
			return (print_error(2, file));
		if (errno == EISDIR)
			return (print_error(4, file));
		return (print_error(18, file));
	}
	close(fd);
	return (0);
}

static int	parse_file(char *file)
{
	int	len;

	if (!file)
		return (print_error(1, "(null)"));
	len = ft_strlen(file);
	if (len < 4 || file[len - 4] != '.'
		|| file[len - 3] != 'c'
		|| file[len - 2] != 'u'
		|| file[len - 1] != 'b')
		return (print_error(1, file));
	if (parse_permisions(file) != 0)
		return (1);
	return (0);
}

int	parser(char *file, t_game *g)
{
	char	**matrix;

	if (parse_file(file) == 1)
		return (1);
	matrix = parse_content(file);
	if (matrix == NULL)
		return (1);
	if (parse_headline(matrix, g) == 1)
		return (free_matrix(matrix), 1);
	if (parse_map(matrix, g) == 1)
		return (free_matrix(matrix), 1);
	free_matrix(matrix);
	return (0);
}

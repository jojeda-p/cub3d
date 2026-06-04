/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:42:35 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/03 17:54:56 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int	parse_file(char *file)
{
	int	i;
	int	fd;

	i = ft_strlen(file) -1;
	if (file[i] != 'b' || file[i - 1] != 'u' || file[i - 2] != 'c' ||
		file[i - 3] != '.')
		return (1);
	if (parse_permisions(file) != 0)
		return (1);
	close(fd);
	return (0);
}

int	parser(char *file, t_game *g)
{
	char	**matrix;
	if (parse_file(file) != 0)
		return (1);
	matrix = parse_content(file, g);
	if (matrix == NULL)
		return (1);
	if (parse_headline(matrix, g) != 0)
		return (1);
	free_matrix(matrix);
	return (0);
}
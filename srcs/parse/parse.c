/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:42:35 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 13:30:16 by jojeda-p         ###   ########.fr       */
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
       		return (print_error(2, file));
    	else if (errno == EACCES)
        	return (print_error(3, file));
    	else if (errno == EISDIR)
        	return (print_error(4, file));
	}
	close(fd);
	return (0);
}

int	parse_file(char *file)
{
	int	i;

	i = ft_strlen(file) -1;
	if (file[i] != 'b' || file[i - 1] != 'u' || file[i - 2] != 'c' ||
		file[i - 3] != '.')
		return (1);
	if (parse_permisions(file) != 0)
		return (1);
	return (0);
}

int	parser(char *file, t_game *g)
{
	char	**matrix;
	if (parse_file(file) != 0)
		return (1);
	matrix = parse_content(file);
	if (matrix == NULL)
		return (1);
	if (parse_headline(matrix, g) != 0)
		return (1);
	free_matrix(matrix);
	return (0);
}
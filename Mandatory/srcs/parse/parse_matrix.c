/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:13:11 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/08/19 14:30:00 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static char	*add_char(char *line, char c)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(line);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (free(line), NULL);
	i = 0;
	while (i < len)
	{
		new[i] = line[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	free(line);
	return (new);
}

static int	add_line(char ***matrix, char *line)
{
	char	**new;
	int		i;

	i = 0;
	while ((*matrix)[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (1);
	i = 0;
	while ((*matrix)[i])
	{
		new[i] = (*matrix)[i];
		i++;
	}
	new[i] = line;
	new[i + 1] = NULL;
	free(*matrix);
	*matrix = new;
	return (0);
}

static int	store_char(char ***matrix, char **line, char c)
{
	*line = add_char(*line, c);
	if (!*line)
		return (1);
	if (c != '\n')
		return (0);
	if (add_line(matrix, *line) != 0)
		return (1);
	*line = ft_strdup("");
	if (!*line)
		return (1);
	return (0);
}

static char	**read_matrix(int fd)
{
	char	**matrix;
	char	*line;
	char	c;
	int		ret;

	matrix = malloc(sizeof(char *));
	line = ft_strdup("");
	if (!matrix || !line)
		return (free(matrix), free(line), NULL);
	matrix[0] = NULL;
	ret = read(fd, &c, 1);
	while (ret > 0)
	{
		if (store_char(&matrix, &line, c) != 0)
			return (free(line), free_matrix(matrix), NULL);
		ret = read(fd, &c, 1);
	}
	if (ret < 0)
		return (free(line), free_matrix(matrix), NULL);
	if (line[0] && add_line(&matrix, line) != 0)
		return (free(line), free_matrix(matrix), NULL);
	if (!line[0])
		free(line);
	return (matrix);
}

char	**parse_content(char *file)
{
	char	**matrix;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error(18, file), NULL);
	matrix = read_matrix(fd);
	close(fd);
	if (!matrix)
		return (print_error(16, NULL), NULL);
	return (matrix);
}

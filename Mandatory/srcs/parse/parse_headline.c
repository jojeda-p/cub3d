/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:22:25 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 20:15:11 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	parse_texture(char **matrix, t_game *g, char *s)
{
	int		i;
	char	*path;

	i = 0;
	while (matrix[i] && i < g->map.init)
	{
		if (matrix[i][0] == s[0] && matrix[i][1] == s[1])
		{
			path = ft_strdup(matrix[i] + 3);
			if (!path)
				return (1);
			path = clean_path(path);
			if (!path)
				return (1);
			if (parse_texture_name(path) == 1)
				return (free(path), print_error(7, s));
			if (parse_permisions(path) != 0)
				return (free(path), 1);
			if (get_texture_path(g, s, path) == 1)
				return (free(path), 1);
		}
		i++;
	}
	return (0);
}

static int	save_color(t_game *g, int value, char *s)
{
	if (s[0] == 'F')
	{
		if (g->config.floor_found)
			return (print_error(17, s));
		g->config.floor_color = value;
		g->config.floor_found = 1;
	}
	else
	{
		if (g->config.ceiling_found)
			return (print_error(17, s));
		g->config.ceiling_color = value;
		g->config.ceiling_found = 1;
	}
	return (0);
}

static int	process_color(t_game *g, char *raw, char *s)
{
	char	*color;
	int		value;

	color = ft_strdup(raw);
	if (!color)
		return (print_error(16, NULL));
	color = clean_path(color);
	if (!color)
		return (print_error(16, NULL));
	if (get_color_hex(color, &value) != 0)
	{
		free(color);
		return (print_error(9, s));
	}
	free(color);
	return (save_color(g, value, s));
}

static int	parse_color(char **matrix, t_game *g, char *s)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (matrix[i] && i < g->map.init)
	{
		if (matrix[i][0] == s[0]
			&& (matrix[i][1] == ' ' || matrix[i][1] == '\t'))
		{
			if (process_color(g, matrix[i] + 2, s) != 0)
				return (1);
			found = 1;
		}
		i++;
	}
	if (!found)
		return (print_error(6, s));
	return (0);
}

int	parse_headline(char **matrix, t_game *g)
{
	if (get_map_init(matrix, g) != 0)
		return (1);
	if (validate_header(matrix, g) != 0)
		return (1);
	if (parse_texture(matrix, g, "NO") != 0)
		return (1);
	if (parse_texture(matrix, g, "SO") != 0)
		return (1);
	if (parse_texture(matrix, g, "EA") != 0)
		return (1);
	if (parse_texture(matrix, g, "WE") != 0)
		return (1);
	if (parse_color(matrix, g, "F") != 0)
		return (1);
	if (parse_color(matrix, g, "C") != 0)
		return (1);
	if (check_textures(g) == 1)
		return (1);
	return (0);
}

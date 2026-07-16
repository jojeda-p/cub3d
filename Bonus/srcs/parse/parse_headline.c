/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:22:25 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/15 15:02:32 by jojeda-p         ###   ########.fr       */
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

static int	process_color(t_game *g, char *raw, char *s)
{
	char	*color;

	color = ft_strdup(raw);
	if (!color)
		return (1);
	color = clean_path(color);
	if (!color)
		return (1);
	if (check_color_number(color, s) == 1)
		return (free(color), 1);
	if (s[0] == 'F')
		g->config.floor_color = get_color_hex(color, s);
	else if (s[0] == 'C')
		g->config.ceiling_color = get_color_hex(color, s);
	if (g->config.floor_color == 1 || g->config.ceiling_color == 1)
		return (free(color), 1);
	free(color);
	return (0);
}

static int	parse_color(char **matrix, t_game *g, char *s)
{
	int	i;

	i = 0;
	while (matrix[i] && i < g->map.init)
	{
		if (matrix[i][0] == s[0])
			return (process_color(g, matrix[i] + 2, s));
		i++;
	}
	return (print_error(6, s));
}

static void	get_map_init(char **matrix, t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] != '1' && matrix[i][j] != ' ')
				break ;
			if (matrix[i][j + 1] == '\n')
				g->map.init = i;
			j++;
		}
		i++;
	}
}

int	parse_headline(char **matrix, t_game *g)
{
	get_map_init(matrix, g);
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

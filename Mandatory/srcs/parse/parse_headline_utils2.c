/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:01:56 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 14:47:57 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	check_textures(t_game *g)
{
	if (!g->tex[0].path)
		return (print_error(5, "NO"));
	if (!g->tex[1].path)
		return (print_error(5, "SO"));
	if (!g->tex[2].path)
		return (print_error(5, "EA"));
	if (!g->tex[3].path)
		return (print_error(5, "WE"));
	if (!g->config.ceiling_found)
		return (print_error(6, "C"));
	if (!g->config.floor_found)
		return (print_error(6, "F"));
	return (0);
}

int	get_color_hex(char *color, int *hex)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	if (get_component(color, &i, &r) || color[i] != ',')
		return (1);
	i++;
	if (get_component(color, &i, &g) || color[i] != ',')
		return (1);
	i++;
	if (get_component(color, &i, &b) || color[i] != '\0')
		return (1);
	*hex = (r << 16) | (g << 8) | b;
	return (0);
}

int	is_map_start(char *line)
{
	int	i;
	int	has_wall;

	i = 0;
	has_wall = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '1')
			return (0);
		if (line[i] == '1')
			has_wall = 1;
		i++;
	}
	return (has_wall);
}

int	get_map_init(char **matrix, t_game *g)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (is_map_start(matrix[i]))
		{
			g->map.init = i;
			return (0);
		}
		i++;
	}
	return (print_error(19, NULL));
}

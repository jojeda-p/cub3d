/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:01:56 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/08/19 14:56:53 by jojeda-p         ###   ########.fr       */
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
	int	has_map_char;

	i = 0;
	has_map_char = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		if (line[i] != ' ')
			has_map_char = 1;
		i++;
	}
	return (has_map_char);
}

static int	valid_element(char *line)
{
	if (line[0] == '\n' && line[1] == '\0')
		return (1);
	if (((line[0] == 'N' && line[1] == 'O')
			|| (line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'E' && line[1] == 'A')
			|| (line[0] == 'W' && line[1] == 'E'))
		&& line[2] == ' ')
		return (1);
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
		return (1);
	return (0);
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
		if (!valid_element(matrix[i]))
			return (print_error(20, NULL));
		i++;
	}
	return (print_error(19, NULL));
}

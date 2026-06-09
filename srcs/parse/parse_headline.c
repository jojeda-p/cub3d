/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:22:25 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/09 13:39:25 by jojeda-p         ###   ########.fr       */
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
			path = clean_path(path);
			if (parse_texture_name(path) == 1)
				return (print_error(7, s));
			if (parse_permisions(path) != 0)
				return (1);
			if (get_texture_path(g, s, path) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	parse_color(char **matrix, t_game *g, char *s)
{
	int		i;
	char	*color;

	i = 0;
	while (matrix[i] && i < g->map.init)
	{
		if (matrix[i][0] == s[0])
		{
			color = ft_strdup(matrix[i] + 2);
			color = clean_path(color);
			if (check_color_number(color, s) == 1)
				return (1);
			if (s[0] == 'F')
				g->config.floor_color = get_color_hex(color, s);
			else if (s[0] == 'C')
				g->config.ceiling_color = get_color_hex(color, s);
			if (g->config.floor_color == 1 || g->config.ceiling_color == 1)
				return (1);
			return (0);
		}
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

static int	check_textures(t_game *g)
{
	if (!g->tex[0].path)
		return (print_error(5, "NO"));
	if (!g->tex[1].path)
		return (print_error(5, "SO"));
	if (!g->tex[2].path)
		return (print_error(5, "EA"));
	if (!g->tex[3].path)
		return (print_error(5, "WE"));
	if (!g->config.ceiling_color)
		return (print_error(6, "C"));
	if (!g->config.ceiling_color)
		return (print_error(6, "F"));
	return (0);
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

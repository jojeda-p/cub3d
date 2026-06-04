/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:22:25 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 18:06:10 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*pone el path en la estructura final y comprueba que no se repita la textura*/
static int	get_texture_path(t_game *g, char *s, int *found, char *path)
{
	if (s[0] == 'N' && found[0] == 0)
	{
		g->tex[0].path = path;
		found[0] = 1;
		return (0);
	}
	else if (s[0] == 'S' && found[0] == 0)
	{
		g->tex[1].path = path;
		found[1] = 1;
		return (0);
	}
	else if (s[0] == 'E' && found[0] == 0)
	{
		g->tex[2].path = path;
		found[2] = 1;
		return (0);
	}
	else if (s[0] == 'W' && found[0] == 0)
	{
		g->tex[3].path = path;
		found[3] = 1;
		return (0);
	}
	return (print_error(8, s));
}

int	parse_texture_name(char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	if (path[i] != 'm' || path[i - 1] != 'p'  || path[i - 2] != 'x' ||
		path[i - 3] != '.')
		return (print_error(1, path));
	return (0);
}

static int	parse_texture(char **matrix, t_game *g, char *s)
{
	int		i;
	char	*path;
	int		found[4];

	i = 0;
	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	found[3] = 0;
	while(i < 4)
	{
		if (matrix[i][0] == s[0] && matrix[i][1] == s[1])
		{
			path = ft_strdup(matrix[i] + 3);
			if (parse_texture_name(path) == 1)
				return (print_error(7, s));
			if (parse_permisions(path) != 0)
				return (1);
			return (get_texture_path(g, s, found, path));
		}
		i++;
	}
	return (print_error(5, s));
}

static int	get_color_hex(char *color, char *s)
{
	int	r;
	int	g;
	int	b;
	int	i;
	
	r = ft_atoi_color(color);
	if (r == -1)
		return (print_error(9, s));
	i = 0;
	while (color[i] && ft_isnum(color[i]))
		i++;
	g = ft_atoi_color(color + i + 1);
	if (g == -1)
		return (print_error(9, s));
	i++;
	while (color[i] && ft_isnum(color[i]))
		i++;
	b = ft_atoi_color(color + i + 1);
	if (b == -1)
		return (print_error(9, s));
	return ((r << 16) | (g << 8) | b);
}

int	parse_color(char **matrix, t_game *g, char *s)
{
	int		i;
	char	*color;

	i = 5;
	while(i < 7)
	{
		if (matrix[i][0] == s[0])
		{
			color = ft_strdup(matrix[i] + 2);
		 	if (s[0] == 'F')
				g->config.floor_color = get_color_hex(color, s);
			else if (s[0] == 'C')
				g->config.ceiling_color = get_color_hex(color, s);
			return (0);
		}
		i++;
	}
	return (print_error(6, s));
}

int	parse_headline(char **matrix, t_game *g)
{
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
	return (0);
}
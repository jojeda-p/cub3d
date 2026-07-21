/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:03:15 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 14:07:56 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>

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
		return (free(color), print_error(9, s));
	free(color);
	return (save_color(g, value, s));
}

int	parse_color(char **matrix, t_game *g, char *s)
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

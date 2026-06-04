/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:22:25 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/03 18:31:53 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char **matrix, t_game *g, char *s)
{
	int		i;
	char	*path;

	i = 0;
	while(i < 4)
	{
		if (matrix[i][0] == s[0] && matrix[i][1] == s[1])
		{
			path = ft_strdup(matrix[i] + 3);
			if (parse_permisions(path) != 0)
				return (1);
			if (s[0] == 'N')
				g->tex[0].path = path;
			else if (s[0] == 'S')
				g->tex[1].path = path;
			else if (s[0] == 'E')
				g->tex[2].path = path;
			else if (s[0] == 'W')
				g->tex[3].path = path;
			return (0);
		}
		i++;
	}
	return (print_error(5, s), 1);
}

int	parse_color(char **matrix, t_game *g, char s)
{
	int		i;
	char	*color;

	i = 4;
	while(i < 6)
	{
		if (matrix[i][0] == s)
		{
			color = ft_strdup(matrix[i] + 2);
			if (s == 'F')
				g->floor_color = get_color_binary(color);
			else if (s == 'C')
				g->ceiling_color = get_color_binary(color);
			return (0);
		}
		i++;
	}
	return (print_error(6, s), 1);
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
	if (parse_floor(matrix, g, "C") != 0)
		return (1);
	process_textures();
}
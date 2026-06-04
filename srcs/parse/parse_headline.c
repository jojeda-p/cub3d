/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:22:25 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 12:59:44 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (1);
}

int	parse_texture(char **matrix, t_game *g, char *s)
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
			if (parse_permisions(path) != 0)
				return (1);
			return (get_texture_path(g, s, found, path));
		}
		i++;
	}
	return (print_error(5, s), 1);
}

/* int	parse_color(char **matrix, t_game *g, char *s)
{
	int		i;
	char	*color;

	i = 4;
	while(i < 6)
	{
		if (matrix[i][0] == s[0])
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
} */


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
	/* if (parse_color(matrix, g, "F") != 0)
		return (1);
	if (parse_floor(matrix, g, "C") != 0)
		return (1); */
	/* process_textures(); */
	return (0);
}
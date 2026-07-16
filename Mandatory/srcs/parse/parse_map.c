/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 14:58:04 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 12:44:38 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static int	map_char_parse(char **matrix, t_game *g)
{
	int	i;
	int	j;

	i = g->map.init;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (!valid_char(matrix[i][j]))
				return (print_error(10, "map"));
			if (matrix[i][j] == 'N' || matrix[i][j] == 'S' ||
				matrix[i][j] == 'W' || matrix[i][j] == 'E')
				g->map.spawn++;
			j++;
		}
		i++;
	}
	if (g->map.spawn != 1)
		return (print_error(12, "NULL"));
	return (0);
}

static int	matrix_to_grid(char **matrix, t_game *g)
{
	int	i;
	int	j;
	int	k;

	i = 6;
	k = 0;
	malloc_grid(matrix, g);
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '\n')
				g->map.grid[k][j] = '\0';
			else
				g->map.grid[k][j] = matrix[i][j];
			j++;
		}
		g->map.grid[k][j] = '\0';
		i++;
		k++;
	}
	g->map.grid[k] = NULL;
	return (0);
}

void	get_player(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			if (g->map.grid[i][j] == 'N' || g->map.grid[i][j] == 'S' ||
				g->map.grid[i][j] == 'W' || g->map.grid[i][j] == 'E')
			{
				g->player.y = (double)i + 0.5;
				g->player.x = (double)j + 0.5;
				get_dir(g->map.grid[i][j], g);
				g->map.grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	parse_map(char **matrix, t_game *g)
{
	g->map.spawn = 0;
	g->map.anim = 0;
	g->map.door = 0;
	if (map_char_parse(matrix, g) == 1)
		return (1);
	if (matrix_to_grid(matrix, g) == 1)
		return (1);
	if (init_map(g) == 1)
	{
		free_matrix(g->map.grid);
		g->map.grid = NULL;
		return (1);
	}
	if (parse_flood_fill(g) == 1)
		return (1);
	return (0);
}

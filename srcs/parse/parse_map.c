/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 14:58:04 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/05 14:19:46 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

static int	map_char_parse(char **matrix)
{
	int	i;
	int	j;
	int	spawn;

	i = 6;
	spawn = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] != ' ' && matrix[i][j] != '0' &&
				matrix[i][j] != '1' && matrix[i][j] != 'N' &&
				matrix[i][j] != '\n')
				return (print_error(10, "map"));
			if (matrix[i][j] == 'N')
				spawn++;
			j++;
		}
		i++;
	}
	if (spawn != 1)
		return (print_error(12, "NULL"));
	return (0);
}

void	malloc_grid(char **matrix, t_game *g)
{
	int		i;
	int		j;
	int		k;

	i = 6;
	k = 0;
	while (matrix[i])
	{
		i++;
		k++;
	}
	g->map.grid = malloc(sizeof(char *) * (k + 1));
	i = 6;
	k = 0;
	while (matrix[i])
	{
		j = ft_strlen(matrix[i]) + 1;
		g->map.grid[k] = malloc(sizeof(char) * j);
		i++;
		k++;
	}
	g->map.grid[k] = NULL;
}

int	matrix_to_grid(char **matrix, t_game *g)
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

int	get_width(t_game *g)
{
	int	i;
	int	j;
	int	longest;
	
	i = 0;
	longest = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
			j++;
		if (longest < j)
			longest = j;
		i++;
	}
	return (longest);
}

int	get_height(t_game *g)
{
	int	i;

	i = 0;
	while (g->map.grid[i])
		i++;
	return (i);
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
			if (g->map.grid[i][j] == 'N')
			{
				g->player.y = (double)i + 0.5;
				g->player.x = (double)j + 0.5;
				g->map.grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_map(t_game *g)
{
	g->map.width = get_width(g);
	g->map.height = get_height(g);
	get_player(g);
	g->map.tile_size = 64;
	g->player.x = (g->player.x * g->map.tile_size);
	g->player.y = (g->player.y * g->map.tile_size);
	g->player.dir = 4.0;
	g->player.move_speed = 3;
	g->player.rot_speed = 0.05;
}

int	parse_map(char **matrix, t_game *g)
{
	if (map_char_parse(matrix) == 1)
		return (1);
	if (matrix_to_grid(matrix, g) == 1)
		return (1);
	init_map(g);
	if (parse_flood_fill(g) == 1)
		return (1);
	return (0);
}

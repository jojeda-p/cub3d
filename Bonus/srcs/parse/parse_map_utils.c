/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:42:48 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 16:12:40 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>
#include <stdlib.h>

static void	get_map_size(char **matrix, t_game *g)
{
	int	i;
	int	len;
	int	last;

	i = g->map.init;
	last = i;
	g->map.width = 0;
	while (matrix[i])
	{
		len = 0;
		while (matrix[i][len] && matrix[i][len] != '\n')
			len++;
		if (len > 0)
			last = i + 1;
		if (len > g->map.width)
			g->map.width = len;
		i++;
	}
	g->map.height = last - g->map.init;
}

int	malloc_grid(char **matrix, t_game *g)
{
	int	i;

	get_map_size(matrix, g);
	g->map.grid = malloc(sizeof(char *) * (g->map.height + 1));
	if (!g->map.grid)
		return (1);
	i = 0;
	while (i < g->map.height)
	{
		g->map.grid[i] = malloc(g->map.width + 1);
		if (!g->map.grid[i])
		{
			g->map.grid[i] = NULL;
			free_matrix(g->map.grid);
			g->map.grid = NULL;
			return (1);
		}
		i++;
	}
	g->map.grid[i] = NULL;
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

void	get_dir(char dir, t_game *g)
{
	if (dir == 'N')
	{
		g->player.dir = 4.71238898;
	}
	else if (dir == 'S')
	{
		g->player.dir = 1.570796327;
	}
	else if (dir == 'W')
	{
		g->player.dir = 3.141592654;
	}
	else if (dir == 'E')
	{
		g->player.dir = 0;
	}
}

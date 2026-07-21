/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:42:48 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 15:06:39 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	count_rows(char **matrix, int start)
{
	int	i;
	int	k;

	i = start;
	k = 0;
	while (matrix[i])
	{
		i++;
		k++;
	}
	return (k);
}

int	malloc_grid(char **matrix, t_game *g)
{
	int	i;
	int	k;
	int	rows;

	rows = count_rows(matrix, g->map.init);
	g->map.grid = malloc(sizeof(char *) * (rows + 1));
	if (!g->map.grid)
		return (1);
	i = g->map.init;
	k = 0;
	while (matrix[i])
	{
		g->map.grid[k] = malloc(sizeof(char) * (ft_strlen(matrix[i]) + 1));
		if (!g->map.grid[k])
		{
			g->map.grid[k] = NULL;
			free_matrix(g->map.grid);
			g->map.grid = NULL;
			return (1);
		}
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
		g->player.dir = 0;
	}
	else if (dir == 'E')
	{
		g->player.dir = 3.141592654;
	}
}

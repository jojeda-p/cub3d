/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:20:33 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/08 15:04:47 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	map_flood_fill(char **map, int x, int y, int *open)
{
	if (y < 0 || !map[y])
	{
		*open = 1;
		return ;
	}
	if (x < 0 || x >= (int)ft_strlen(map[y]))
	{
		*open = 1;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'X')
		return ;
	if (map[y][x] == ' ')
	{
		map[y][x] = 'X';
		*open = 1;
		return ;
	}
	map[y][x] = 'V';
	map_flood_fill(map, x, y + 1, open);
	map_flood_fill(map, x, y - 1, open);
	map_flood_fill(map, x + 1, y, open);
	map_flood_fill(map, x - 1, y, open);
}

static char	**alloc_grid(char **grid, int size)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (grid[i])
	{
		copy[i] = malloc(sizeof(char) * (ft_strlen(grid[i]) + 1));
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**copy_grid(char **grid)
{
	char	**copy;
	int		i;
	int		j;

	i = 0;
	while (grid[i])
		i++;
	copy = alloc_grid(grid, i);
	if (!copy)
		return (NULL);
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			copy[i][j] = grid[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	return (copy);
}

int	parse_flood_fill(t_game *g)
{
	char	**map;
	int		x;
	int		y;
	int		open;

	open = 0;
	map = copy_grid(g->map.grid);
	x = (int)(g->player.x / g->map.tile_size - 0.5);
	y = (int)(g->player.y / g->map.tile_size - 0.5);
	map_flood_fill(map, x, y, &open);
	if (open)
		return (free_matrix(map), print_error(13, "map"));
	free_matrix(map);
	return (0);
}
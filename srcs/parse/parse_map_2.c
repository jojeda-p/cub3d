/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:20:33 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/22 17:11:28 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static void	mark_door_anim(char c, t_game *g, int x, int y)
{
	if (c == 'A')
	{
		g->map.anim--;
		g->sprite[g->map.anim].x = x * g->map.tile_size + g->map.tile_size / 2;
		g->sprite[g->map.anim].y = y * g->map.tile_size + g->map.tile_size / 2;
	}
	if (c == 'D')
	{
		g->map.door--;
		g->door[g->map.door].x = x * g->map.tile_size + g->map.tile_size / 2;
		g->door[g->map.door].y = y * g->map.tile_size + g->map.tile_size / 2;
		g->door[g->map.door].open_progress = 0.0;
		g->door[g->map.door].open = 0;
	}
}

static void	map_flood_fill(char **map, int x, int y, t_game *g)
{
	if (y < 0 || !map[y])
	{
		g->map.open = 1;
		return ;
	}
	if (x < 0 || x >= (int)ft_strlen(map[y]))
	{
		g->map.open = 1;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'V' || map[y][x] == 'X')
		return ;
	if (map[y][x] == ' ')
	{
		map[y][x] = 'X';
		g->map.open = 1;
		return ;
	}
	if (map[y][x] == 'D' || map[y][x] == 'A')
		mark_door_anim(map[y][x], g, x, y);
	map[y][x] = 'V';
	map_flood_fill(map, x, y + 1, g);
	map_flood_fill(map, x, y - 1, g);
	map_flood_fill(map, x + 1, y, g);
	map_flood_fill(map, x - 1, y, g);
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

static char	**copy_grid(char **grid)
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

int	check_door(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				if (i == 0 || j == 0 || !map[i + 1] || map[i][j + 1] == '\0')
					return (1);
				if (!((map[i - 1][j] == '1' && map[i + 1][j] == '1')
					|| (map[i][j - 1] == '1' && map[i][j + 1] == '1')))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_flood_fill(t_game *g)
{
	char	**map;
	int		x;
	int		y;

	g->map.open = 0;
	map = copy_grid(g->map.grid);
	x = (int)(g->player.x / g->map.tile_size - 0.5);
	y = (int)(g->player.y / g->map.tile_size - 0.5);
	map_flood_fill(map, x, y, g);
	if (g->map.open)
		return (free_matrix(map), print_error(13, "map"));
	if (g->map.anim != 0 || g->map.door != 0)
		return (free_matrix(map), print_error(14, "map"));
	if (check_door(g->map.grid) == 1)
		return (free_matrix(map), print_error(15, "map"));
	free_matrix(map);
	return (0);
}

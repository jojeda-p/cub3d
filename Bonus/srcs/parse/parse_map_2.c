/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:20:33 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 15:21:17 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>
#include <stdlib.h>

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

static int	check_all_areas(char **map, t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				map_flood_fill(map, x, y, g);
				if (g->map.open)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
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
		{
			while (i > 0)
			{
				i--;
				free(copy[i]);
			}
			free(copy);
			return (NULL);
		}
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

int	parse_flood_fill(t_game *g)
{
	char	**map;

	g->map.open = 0;
	map = copy_grid(g->map.grid);
	if (!map)
		return (print_error(16, NULL));
	if (check_all_areas(map, g))
		return (free_matrix(map), print_error(13, "map"));
	free_matrix(map);
	return (0);
}

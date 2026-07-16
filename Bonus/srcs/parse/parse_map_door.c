/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_door.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:01:30 by josu              #+#    #+#             */
/*   Updated: 2026/07/16 15:55:20 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mark_door_anim(char c, t_game *g, int x, int y)
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
		g->door[g->map.door].map_x = x * g->map.tile_size + g->map.tile_size
			/ 2;
		g->door[g->map.door].map_y = y * g->map.tile_size + g->map.tile_size
			/ 2;
		g->door[g->map.door].open_progress = 0.0;
		g->door[g->map.door].target_open = 0;
	}
}

static char	map_cell(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y])
		return (' ');
	if (x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

static int	is_valid_door(char **map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = map_cell(map, i - 1, j);
	down = map_cell(map, i + 1, j);
	left = map_cell(map, i, j - 1);
	right = map_cell(map, i, j + 1);
	if (up == '1' && down == '1')
		return (1);
	if (left == '1' && right == '1')
		return (1);
	return (0);
}

static void	set_door_dir(t_game *g, char **map, int i, int j)
{
	if (map_cell(map, i - 1, j) == '1'
		&& map_cell(map, i + 1, j) == '1')
		g->door[g->map.door].dir = 1;
	else
		g->door[g->map.door].dir = 0;
	g->map.door++;
}

int	check_door(t_game *g, char **map)
{
	int	i;
	int	j;

	i = 0;
	g->map.door = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				if (!is_valid_door(map, i, j))
					return (1);
				set_door_dir(g, map, i, j);
			}
			j++;
		}
		i++;
	}
	return (0);
}

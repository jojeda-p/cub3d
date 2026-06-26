/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_door.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:01:30 by josu              #+#    #+#             */
/*   Updated: 2026/06/26 16:13:04 by josu             ###   ########.fr       */
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
		g->door[g->map.door].open_progress = 0.0;
		g->door[g->map.door].target_open = 0;
	}
}

static int	is_valid_door(char **map, int i, int j)
{
	if (i == 0 || j == 0)
		return (0);
	if (!map[i + 1] || map[i][j + 1] == '\0')
		return (0);
	if (map[i - 1][j] == '1' && map[i + 1][j] == '1')
		return (1);
	if (map[i][j - 1] == '1' && map[i][j + 1] == '1')
		return (1);
	return (0);
}

static void	set_door_dir(t_game *g, char **map, int i, int j)
{
	if (map[i - 1][j] == '1' && map[i + 1][j] == '1')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:29:46 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/02 17:24:37 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>

static char	*const	g_temp_map[] =
{
	"111111111111111",
	"100000000000001",
	"101111111111101",
	"100000000000001",
	"101111011111101",
	"100001000000001",
	"100001011111101",
	"100000000000001",
	"1000000N0000001",
	"111111111111111",
	NULL
};

int	temp_init_map(t_game *g, char *file)
{
	(void)file;
	g->map.grid = (char **)g_temp_map;
	g->map.width = 15;
	g->map.height = 10;
	g->map.tile_size = 64;
	g->player_x = (7.5 * g->map.tile_size);
	g->player_y = (8.5 * g->map.tile_size);
	g->player_dir = 4.0;
	g->move_speed = 3;
	g->rot_speed = 0.05;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:29:46 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/05 12:48:04 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>

static char	*const	g_temp_map[] =
{
	"1111111111111111",
	"10000000000000001",
	"10111111111110001",
	"10000000000000001",
	"10111101111110001",
	"10000100000000001",
	"10000101111110001",
	"1000000N000000111",
	"100000000000001",
	"100000000000001",
	"100000000000001",
	"111111111111111",
	NULL
};

int	temp_init_map(t_game *g, char *file)
{
	(void)file;
	g->map.grid = (char **)g_temp_map;
	g->map.width = 17;
	g->map.height = 12;
	g->map.tile_size = 64;
	g->player.x = (7.5 * g->map.tile_size);
	g->player.y = (8.5 * g->map.tile_size);
	g->player.dir = 4.0;
	g->player.move_speed = 3;
	g->player.rot_speed = 0.05;
	return (0);
}

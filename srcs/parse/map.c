/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:29:46 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/05/28 12:00:17 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stddef.h>

static char	*const	g_temp_map[] =
{
	"1111111111",
	"1000000001",
	"1011111101",
	"1000000101",
	"1011100101",
	"1000100001",
	"1000N00001",
	"1111111111",
	NULL
};

int	temp_init_map(t_game *g, char *file)
{
	(void)file;
	g->map.grid = (char **)g_temp_map;
	g->map.width = 10;
	g->map.height = 8;
	g->map.tile_size = 64;
	g->player_x = (4.5 * g->map.tile_size);
	g->player_y = (6.5 * g->map.tile_size);
	g->player_dir = 4.71238898;
	g->move_speed = 4.0;
	g->rot_speed = 0.08;
	return (0);
}
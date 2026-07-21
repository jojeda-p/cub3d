/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:46:44 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

void	load_door(t_game *g)
{
	int	i;

	if (g->config.door == 0)
		return ;
	i = 0;
	while (i < g->config.door)
	{
		g->door[i].tex.path = "assets/puerta.xpm";
		g->door[i].open_progress = 0.0;
		g->door[i].target_open = 0;
		i++;
	}
}

static void	update_door_loop(t_door_aux *da, t_game *g)
{
	da->door_x = (g->door[da->i].map_x / g->map.tile_size) + 0.5;
	da->door_y = (g->door[da->i].map_y / g->map.tile_size) + 0.5;
	da->dx = da->pos_x - da->door_x;
	da->dy = da->pos_y - da->door_y;
	da->perp_dist = sqrt(da->dx * da->dx + da->dy * da->dy);
	if (da->perp_dist <= 2.0)
		g->door[da->i].target_open = 1;
	else
		g->door[da->i].target_open = 0;
	if (g->door[da->i].target_open == 1)
	{
		g->door[da->i].open_progress += da->speed;
		if (g->door[da->i].open_progress > 1.0)
			g->door[da->i].open_progress = 1.0;
	}
	else
	{
		g->door[da->i].open_progress -= da->speed;
		if (g->door[da->i].open_progress < 0.0)
			g->door[da->i].open_progress = 0.0;
	}
	da->i++;
}

void	update_doors(t_game *g)
{
	t_door_aux	da;

	da.i = 0;
	da.speed = 0.035;
	da.pos_x = g->player.x / g->map.tile_size;
	da.pos_y = g->player.y / g->map.tile_size;
	while (da.i < g->config.door)
		update_door_loop(&da, g);
}

int	load_door_texture(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->config.door)
	{
		g->door[i].tex.img = mlx_xpm_file_to_image(g->mlx,
				g->door[i].tex.path, &g->door[i].tex.width,
				&g->door[i].tex.height);
		if (!g->door[i].tex.img)
			return (1);
		g->door[i].tex.addr = mlx_get_data_addr(g->door[i].tex.img,
				&g->door[i].tex.bpp, &g->door[i].tex.line_len,
				&g->door[i].tex.endian);
		if (!g->door[i].tex.addr)
			return (1);
		i++;
	}
	return (0);
}

int	find_door(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->config.door)
	{
		if (g->door[i].map_x / g->map.tile_size == x
			&& g->door[i].map_y / g->map.tile_size == y)
			return (i);
		i++;
	}
	return (-1);
}

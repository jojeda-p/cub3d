/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:13:15 by josu              #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

void	calculate_door_projection(t_game *g, int i)
{
	if (!isfinite(g->door[i].perp_dist) || g->door[i].perp_dist <= 0.0)
		g->door[i].perp_dist = 1e-6;
	g->door[i].line_height = (int)((double)g->config.height
			/ g->door[i].perp_dist);
	g->door[i].draw_start = -g->door[i].line_height / 2
		+ g->config.height / 2;
	g->door[i].draw_end = g->door[i].line_height / 2
		+ g->config.height / 2;
	if (g->door[i].draw_start < 0)
		g->door[i].draw_start = 0;
	if (g->door[i].draw_end >= g->config.height)
		g->door[i].draw_end = g->config.height - 1;
}

static void	init_door_aux_2(t_game *g, t_door_aux *da)
{
	if (g->ray.ray_dir_x < 0)
	{
		da->step_x = -1;
		da->side_dist_x = (da->pos_x - da->map_x) * da->delta_dist_x;
	}
	else
	{
		da->step_x = 1;
		da->side_dist_x = (da->map_x + 1.0 - da->pos_x)
			* da->delta_dist_x;
	}
	if (g->ray.ray_dir_y < 0)
	{
		da->step_y = -1;
		da->side_dist_y = (da->pos_y - da->map_y) * da->delta_dist_y;
	}
	else
	{
		da->step_y = 1;
		da->side_dist_y = (da->map_y + 1.0 - da->pos_y)
			* da->delta_dist_y;
	}
}

void	init_door_aux(t_game *g, t_door_aux *da)
{
	da->pos_x = g->player.x / g->map.tile_size;
	da->pos_y = g->player.y / g->map.tile_size;
	da->map_x = (int)da->pos_x;
	da->map_y = (int)da->pos_y;
	if (fabs(g->ray.ray_dir_x) < 1e-9)
		da->delta_dist_x = 1e30;
	else
		da->delta_dist_x = fabs(1.0 / g->ray.ray_dir_x);
	if (fabs(g->ray.ray_dir_y) < 1e-9)
		da->delta_dist_y = 1e30;
	else
		da->delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
	init_door_aux_2(g, da);
}

void	step_door_cast(t_door_aux *da)
{
	if (da->side_dist_x < da->side_dist_y)
	{
		da->side_dist_x += da->delta_dist_x;
		da->map_x += da->step_x;
		da->side = 0;
	}
	else
	{
		da->side_dist_y += da->delta_dist_y;
		da->map_y += da->step_y;
		da->side = 1;
	}
}

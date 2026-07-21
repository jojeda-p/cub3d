/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:10:28 by josu              #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static int	door_cast_out(t_game *g, t_door_aux *da)
{
	if (da->map_x < 0 || da->map_x >= g->map.width)
		return (1);
	if (da->map_y < 0 || da->map_y >= g->map.height)
		return (1);
	return (0);
}

static void	calculate_door_hit(t_game *g, t_door_aux *da)
{
	if (da->side == 0)
	{
		da->perp_dist = da->side_dist_x - da->delta_dist_x * 0.5;
		da->wall_x = da->pos_y + da->perp_dist * g->ray.ray_dir_y;
		da->wall_x -= floor(da->wall_x);
		if (g->ray.ray_dir_x < 0)
			da->wall_x = 1.0 - da->wall_x;
	}
	else
	{
		da->perp_dist = da->side_dist_y - da->delta_dist_y * 0.5;
		da->wall_x = da->pos_x + da->perp_dist * g->ray.ray_dir_x;
		da->wall_x -= floor(da->wall_x);
		if (g->ray.ray_dir_y > 0)
			da->wall_x = 1.0 - da->wall_x;
	}
}

static int	set_door_tex_x(t_game *g, t_door_aux *da)
{
	if (da->wall_x < g->door[da->i].open_progress)
		return (0);
	g->door[da->i].tex_x = (int)((da->wall_x
				- g->door[da->i].open_progress)
			* g->door[da->i].tex.width);
	if (g->door[da->i].tex_x < 0)
		g->door[da->i].tex_x = 0;
	if (g->door[da->i].tex_x >= g->door[da->i].tex.width)
		g->door[da->i].tex_x = g->door[da->i].tex.width - 1;
	return (1);
}

static void	draw_door_hit(t_game *g, int column, t_door_aux *da)
{
	da->i = find_door(g, da->map_x, da->map_y);
	if (da->i < 0)
		return ;
	calculate_door_hit(g, da);
	if (da->perp_dist <= 0 || da->perp_dist >= g->ray.z_buf[column])
		return ;
	if (!set_door_tex_x(g, da))
		return ;
	g->door[da->i].perp_dist = da->perp_dist;
	calculate_door_projection(g, da->i);
	draw_door_column(g, column, da->i);
}

void	draw_door_over_wall(t_game *g, int column)
{
	t_door_aux	da;

	init_door_aux(g, &da);
	while (1)
	{
		step_door_cast(&da);
		if (door_cast_out(g, &da))
			return ;
		if (g->map.grid[da.map_y][da.map_x] == '1')
			return ;
		if (g->map.grid[da.map_y][da.map_x] == 'D')
		{
			draw_door_hit(g, column, &da);
			return ;
		}
	}
}

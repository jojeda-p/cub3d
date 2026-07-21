/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:05 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include "mlx.h"
#include <stdio.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void	apply_physics(t_game *g)
{
	double	speed;
	double	d;
	double	current_max;

	d = (g->player.vel_x * g->player.dir_x + g->player.vel_y * g->player.dir_y);
	if (d > 0.1)
		current_max = g->player.max_speed;
	else if (d < -0.1)
		current_max = g->player.max_speed * 0.55;
	else
		current_max = g->player.max_speed * 0.75;
	speed = sqrt(g->player.vel_x * g->player.vel_x
			+ g->player.vel_y * g->player.vel_y);
	if (speed > current_max)
	{
		g->player.vel_x = (g->player.vel_x / speed) * current_max;
		g->player.vel_y = (g->player.vel_y / speed) * current_max;
	}
	g->player.vel_x *= (1.0 - g->player.friction);
	g->player.vel_y *= (1.0 - g->player.friction);
}

static int	is_walkable(t_game *g, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / g->map.tile_size);
	map_y = (int)(y / g->map.tile_size);
	if (map_x < 0 || map_x >= g->map.width
		|| map_y < 0 || map_y >= g->map.height)
		return (0);
	return (g->map.grid[map_y][map_x] != '1');
}

static int	try_slide_x(t_game *g, double new_x)
{
	if (!is_walkable(g, new_x, g->player.y))
		return (0);
	g->player.x = new_x;
	g->player.vel_y = 0;
	return (1);
}

static int	try_slide_y(t_game *g, double new_y)
{
	if (!is_walkable(g, g->player.x, new_y))
		return (0);
	g->player.y = new_y;
	g->player.vel_x = 0;
	return (1);
}

void	move_player(t_game *g)
{
	double	new_x;
	double	new_y;

	apply_physics(g);
	new_x = g->player.x + g->player.vel_x;
	new_y = g->player.y + g->player.vel_y;
	if (is_walkable(g, new_x, new_y))
	{
		g->player.x = new_x;
		g->player.y = new_y;
		return ;
	}
	if (try_slide_x(g, new_x))
		return ;
	if (try_slide_y(g, new_y))
		return ;
	g->player.vel_x = 0;
	g->player.vel_y = 0;
}

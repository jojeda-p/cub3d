/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:05 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 13:10:01 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"
#include <stdio.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static void	normalize_velocity(t_game *g)
{
	double	speed;

	speed = sqrt(g->player.vel_x * g->player.vel_x
			+ g->player.vel_y * g->player.vel_y);
	if (speed > g->player.accel)
	{
		g->player.vel_x = g->player.vel_x / speed * g->player.accel;
		g->player.vel_y = g->player.vel_y / speed * g->player.accel;
	}
}

void	move_player(t_game *g)
{
	double	new_x;
	double	new_y;

	normalize_velocity(g);
	new_x = g->player.x + g->player.vel_x;
	new_y = g->player.y + g->player.vel_y;
	g->player.x = new_x;
	g->player.y = new_y;
	g->player.vel_x = 0;
	g->player.vel_y = 0;
}

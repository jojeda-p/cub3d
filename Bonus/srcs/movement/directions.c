/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:03:29 by julepere          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include <math.h>

void	move_forward(t_game *g)
{
	double	accel;

	accel = (g->player.force / g->player.mass) * 1.0;
	g->player.vel_x += g->player.dir_x * accel;
	g->player.vel_y += g->player.dir_y * accel;
}

void	move_backward(t_game *g)
{
	double	accel;

	accel = (g->player.force / g->player.mass) * 0.6;
	g->player.vel_x -= g->player.dir_x * accel;
	g->player.vel_y -= g->player.dir_y * accel;
}

void	move_left(t_game *g)
{
	double	accel;

	accel = (g->player.force / g->player.mass) * 0.8;
	g->player.vel_x += g->player.dir_y * accel;
	g->player.vel_y -= g->player.dir_x * accel;
}

void	move_right(t_game *g)
{
	double	accel;

	accel = (g->player.force / g->player.mass) * 0.8;
	g->player.vel_x -= g->player.dir_y * accel;
	g->player.vel_y += g->player.dir_x * accel;
}

void	rotate_camera(double angle, t_game *g)
{
	double	old_dir_x;
	double	old_dir_y;
	double	old_cam_x;
	double	old_cam_y;

	old_dir_x = g->player.dir_x;
	old_dir_y = g->player.dir_y;
	old_cam_x = g->camera.plane_x;
	old_cam_y = g->camera.plane_y;
	g->player.dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	g->player.dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	g->camera.plane_x = old_cam_x * cos(angle) - old_cam_y * sin(angle);
	g->camera.plane_y = old_cam_x * sin(angle) + old_cam_y * cos(angle);
}

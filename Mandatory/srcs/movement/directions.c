/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:03:29 by julepere          #+#    #+#             */
/*   Updated: 2026/07/16 12:33:38 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

void	move_forward(t_game *g)
{
	g->player.vel_x += g->player.dir_x;
	g->player.vel_y += g->player.dir_y;
}

void	move_backward(t_game *g)
{
	g->player.vel_x -= g->player.dir_x;
	g->player.vel_y -= g->player.dir_y;
}

void	move_left(t_game *g)
{
	g->player.vel_x += g->player.dir_y;
	g->player.vel_y -= g->player.dir_x;
}

void	move_right(t_game *g)
{
	g->player.vel_x -= g->player.dir_y;
	g->player.vel_y += g->player.dir_x;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:16:48 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include "mlx.h"
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

void	update_speed_limit(t_game *g)
{
	double	target_speed;
	double	target_friction;
	double	target_fov;
	double	scale;

	if (is_sprinting(g))
	{
		target_speed = g->player.sprint_speed;
		target_friction = 0.05;
		target_fov = g->camera.sprint_fov;
	}
	else
	{
		target_speed = g->player.walk_speed;
		target_friction = 0.09;
		target_fov = g->camera.walk_fov;
	}
	g->player.max_speed += (target_speed - g->player.max_speed) * 0.12;
	g->player.friction += (target_friction - g->player.friction) * 0.05;
	g->camera.fov += (target_fov - g->camera.fov) * 0.1;
	scale = tan((g->camera.fov * M_PI / 180.0) / 2.0);
	g->camera.plane_x = -g->player.dir_y * scale;
	g->camera.plane_y = g->player.dir_x * scale;
}

void	update_player(t_game *g)
{
	int		forward;
	int		strafe;
	double	angle;

	angle = 0;
	forward = (g->input.up != 0) - (g->input.down != 0);
	strafe = (g->input.right != 0) - (g->input.left != 0);
	mlx_mouse_hide(g->mlx, g->win);
	if (forward == 1)
		move_forward(g);
	else if (forward == -1)
		move_backward(g);
	if (strafe == 1)
		move_right(g);
	else if (strafe == -1)
		move_left(g);
	update_speed_limit(g);
	move_player(g);
	if (g->input.arrow_left && !g->input.arrow_right)
		angle -= g->player.rot_speed;
	else if (g->input.arrow_right && !g->input.arrow_left)
		angle += g->player.rot_speed;
	angle += update_mouse(g);
	rotate_camera(angle, g);
}

double	update_mouse(t_game *g)
{
	int		x;
	int		y;
	int		delta_x;
	double	angle;

	mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
	if (g->camera.mouse_warped || g->camera.last_mouse_x == -1)
	{
		g->camera.mouse_warped = 0;
		g->camera.last_mouse_x = x;
		return (0);
	}
	delta_x = x - g->camera.last_mouse_x;
	angle = delta_x * g->camera.sensitivity;
	g->camera.last_mouse_x = x;
	if (x < 1 || x > g->config.width - 1
		|| y < 1 || y > g->config.height - 1)
	{
		mlx_mouse_move(g->mlx, g->win,
			g->config.width / 2, g->config.height / 2);
		g->camera.last_mouse_x = g->config.width / 2;
		g->camera.mouse_warped = 1;
	}
	return (angle);
}

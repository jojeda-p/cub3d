/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:05 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/10 18:59:30 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"

void	move_player(t_game *g)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	g->player.vel_x *= g->player.inertia;
	g->player.vel_y *= g->player.inertia;
	new_x = g->player.x + g->player.vel_x;
	new_y = g->player.y + g->player.vel_y;
	map_x = (int)(new_x / g->map.tile_size);
	map_y = (int)(new_y / g->map.tile_size);
	if (map_x < 0 || map_x >= g->map.width
		|| map_y < 0 || map_y >= g->map.height)
		return ;
	if (g->map.grid[map_y][map_x] != '1')
	{
		g->player.x = new_x;
		g->player.y = new_y;
	}
	else
	{
		g->player.vel_x = 0;
		g->player.vel_y = 0;
	}
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
	move_player(g);
	if (g->input.arrow_left && !g->input.arrow_right)
		angle -= g->player.rot_speed;
	else if (g->input.arrow_right && !g->input.arrow_left)
		angle += g->player.rot_speed;
	angle += update_mouse(g);
	rotate_camera(angle, g);
}

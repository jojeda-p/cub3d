/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:05 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 16:31:43 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"

int inertia();

void	rotate_camera(double angle, t_game *g)
{
	double old_dir_x;
	double old_dir_y;
	double old_cam_x;
	double old_cam_y;

	old_dir_x = g->player.dir_x;
	old_dir_y = g->player.dir_y;
	old_cam_x = g->camera.plane_x;
	old_cam_y = g->camera.plane_y;

	g->player.dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	g->player.dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	g->camera.plane_x = old_cam_x * cos(angle) - old_cam_y * sin(angle);
	g->camera.plane_y = old_cam_x * sin(angle) + old_cam_y * cos(angle);
}

double update_mouse(t_game *g)
{
    int     x;
    int     y;
    int     delta_x;
    double  angle;

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
    if (x < 1 || x > g->config.width - 1 || y < 1 || y > g->config.height - 1)
    {
        mlx_mouse_move(g->mlx, g->win, g->config.width / 2, g->config.height / 2);
        g->camera.last_mouse_x = g->config.width / 2;
        g->camera.mouse_warped = 1;
    }
    return (angle);
}

void update_player(t_game *g)
{
	int forward;
	int strafe;
	double angle;

	mlx_mouse_hide(g->mlx, g->win);
	angle = 0;
	forward = (g->input.up != 0) - (g->input.down != 0);
	strafe = (g->input.right != 0) - (g->input.left != 0);
	if(forward == 1)
		move_forward('w', g);
	else if(forward == -1)
		move_backward('s', g);	
	if (strafe == 1)
		move_right('d', g);
	else if (strafe == -1)
		move_left('a', g);
	if (g->input.arrow_left && !g->input.arrow_right)
		angle -= g->player.rot_speed;
	else if (g->input.arrow_right && !g->input.arrow_left)
		angle += g->player.rot_speed;
	angle += update_mouse(g);
	rotate_camera(angle, g);
}

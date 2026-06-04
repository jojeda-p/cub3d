/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:05 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 17:59:17 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"

/* void	inertia(t_game *g, int v)
{
	while(g->player.move_speed > 0)
		g->player.move_speed == g->player.move_speed - (g->player.inertia * v);
} */
void	update_velocity(t_game *g)
{
	double move_x;
	double move_y;
	double len;
	double speed;

	g->player.vel_x;
	g->player.vel_y;
}
void	move_player(t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;

	new_x = g->player.x + g->player.vel_x;
	new_y = g->player.y + g->player.vel_y;
	map_x = (int)(new_x / g->map.tile_size);
	map_y = (int)(new_y / g->map.tile_size);
	if (map_x < 0 || map_x >= g->map.width || map_y < 0 || map_y >= g->map.height)
		return ;
	if (g->map.grid[map_y][map_x] != '1')
		{
			g->player.x = new_x;
			g->player.y = new_y;
		}
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
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	angle = 0;
	forward = (g->input.up != 0) - (g->input.down != 0);
	strafe = (g->input.right != 0) - (g->input.left != 0);
	mlx_mouse_hide(g->mlx, g->win);
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

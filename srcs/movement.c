/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:05 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/02 17:52:27 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"

void	move_forward(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;

	if (c == 'w')
	{
		new_x = g->player_x + g->dir_x * g->move_speed;
		new_y = g->player_y + g->dir_y * g->move_speed;
		map_x = (int)(new_x / g->map.tile_size);
		map_y = (int)(new_y / g->map.tile_size);
		if (map_x < 0 || map_x >= g->map.width || map_y < 0 || map_y >= g->map.height)
			return ;
		if (g->map.grid[map_y][map_x] != '1')
		{
			g->player_x = new_x;
			g->player_y = new_y;
		}
	}
}

void	move_backward(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;

	if (c == 's')
	{
		new_x = g->player_x - g->dir_x * g->move_speed;
		new_y = g->player_y - g->dir_y * g->move_speed;
		map_x = (int)(new_x / g->map.tile_size);
		map_y = (int)(new_y / g->map.tile_size);
		if (map_x < 0 || map_x >= g->map.width || map_y < 0 || map_y >= g->map.height)
			return ;
		if (g->map.grid[map_y][map_x] != '1')
		{
			g->player_x = new_x;
			g->player_y = new_y;
		}
	}
}

void	move_left(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;
	
	if (c == 'a')
	{
		new_x = g->player_x + (g->dir_y) * g->move_speed;
		new_y = g->player_y - (g->dir_x) * g->move_speed;
		map_x = (int)(new_x / g->map.tile_size);
		map_y = (int)(new_y / g->map.tile_size);
		if (map_x < 0 || map_x >= g->map.width || map_y < 0 || map_y >= g->map.height)
			return ;
		if (g->map.grid[map_y][map_x] != '1')
		{
			g->player_x = new_x;
			g->player_y = new_y;
		}
	}
	
}

void	move_right(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;
	
	if (c == 'd')
	{
		new_x = g->player_x - (g->dir_y) * g->move_speed;
		new_y = g->player_y + (g->dir_x) * g->move_speed;
		map_x = (int)(new_x / g->map.tile_size);
		map_y = (int)(new_y / g->map.tile_size);
		if (map_x < 0 || map_x >= g->map.width || map_y < 0 || map_y >= g->map.height)
			return ;
		if (g->map.grid[map_y][map_x] != '1')
		{
			g->player_x = new_x;
			g->player_y = new_y;
		}
	}
}

void	rotate_camera(double angle, t_game *g)
{
	double old_dir_x;
	double old_dir_y;
	double old_cam_x;
	double old_cam_y;

	old_dir_x = g->dir_x;
	old_dir_y = g->dir_y;
	old_cam_x = g->cam_x;
	old_cam_y = g->cam_y;

	g->dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	g->dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	g->cam_x = old_cam_x * cos(angle) - old_cam_y * sin(angle);
	g->cam_y = old_cam_x * sin(angle) + old_cam_y * cos(angle);
}

double update_mouse(t_game *g)
{
    int     x;
    int     y;
    int     delta_x;
    double  angle;

    mlx_mouse_get_pos(g->mlx, g->win, &x, &y);
    if (g->mouse_warped || g->last_mouse_x == -1)
    {
        g->mouse_warped = 0;
        g->last_mouse_x = x;
        return (0);
    }
    delta_x = x - g->last_mouse_x;
    angle = delta_x * g->mouse_sensitivity;
    g->last_mouse_x = x;
    if (x < 1 || x > g->width - 1 || y < 1 || y > g->height - 1)
    {
        mlx_mouse_move(g->mlx, g->win, g->width / 2, g->height / 2);
        g->last_mouse_x = g->width / 2;
        g->mouse_warped = 1;
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
		angle -= g->rot_speed;
	else if (g->input.arrow_right && !g->input.arrow_left)
		angle += g->rot_speed;
	angle += update_mouse(g);
	rotate_camera(angle, g);
}

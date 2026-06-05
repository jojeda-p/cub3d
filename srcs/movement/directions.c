/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:03:29 by julepere          #+#    #+#             */
/*   Updated: 2026/06/04 17:25:59 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	move_forward(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;

	if (c == 'w')
	{
		new_x = g->player.x + g->player.dir_x * g->player.move_speed;
		new_y = g->player.y + g->player.dir_y * g->player.move_speed;
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
}

void	move_backward(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;

	if (c == 's')
	{
		new_x = g->player.x - g->player.dir_x * g->player.move_speed;
		new_y = g->player.y - g->player.dir_y * g->player.move_speed;
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
}

void	move_left(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;
	
	if (c == 'a')
	{
		new_x = g->player.x + (g->player.dir_y) * g->player.move_speed;
		new_y = g->player.y - (g->player.dir_x) * g->player.move_speed;
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
	
}

void	move_right(char c, t_game *g)
{
	double	new_x;
	double	new_y;
	int	map_x;
	int	map_y;
	
	if (c == 'd')
	{
		new_x = g->player.x - (g->player.dir_y) * g->player.move_speed;
		new_y = g->player.y + (g->player.dir_x) * g->player.move_speed;
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
}

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

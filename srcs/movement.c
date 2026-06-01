/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:05 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/01 15:15:11 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(char c, t_game *g)
{
	double	new_x;
	double	new_y;

	if (c == 'w')
	{
		new_x = g->player_x + g->dir_x * g->move_speed;
		new_y = g->player_y + g->dir_y * g->move_speed;
		g->ray.map_x = (int)(new_x / g->map.tile_size);
		g->ray.map_y = (int)(new_y / g->map.tile_size);
		if (g->map.grid[g->ray.map_y][g->ray.map_x] != '1')
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

	if (c == 's')
	{
		new_x = g->player_x - g->dir_x * g->move_speed;
		new_y = g->player_y - g->dir_y * g->move_speed;
		g->ray.map_x = (int)(new_x / g->map.tile_size);
		g->ray.map_x = (int)(new_x / g->map.tile_size);
		if (g->map.grid[g->ray.map_y][g->ray.map_x] == '0')
		{
			g->player_x = new_x;
			g->player_y = new_y;
		}
	}
}

void	move_sides(char c, t_game *g)
{
	if (c == 'a')
	{
		new = g->player_y + g->dir_y * g->move_speed;
	}
	if (c == 'd')
	{
		new = g->player_y - g->dir_y * g->move_speed;
	}
}

void	rotate_camera(char c, t_game *g)
{
	if (c == 'l')
	{
		
	}
	if (c == 'r')
	{
		
	}
}
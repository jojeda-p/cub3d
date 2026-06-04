/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:03:29 by julepere          #+#    #+#             */
/*   Updated: 2026/06/04 13:15:57 by julepere         ###   ########.fr       */
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

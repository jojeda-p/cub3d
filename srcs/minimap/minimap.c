/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:15:16 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/09 18:24:04 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	init_minimap(t_game *g)
{
	g->mm.width = g->config.width / 5;
	g->mm.height = g->config.height / 5;
	g->mm.x = 20;
	g->mm.y = 20;
	g->mm.border = 5;
	g->mm.scale = 20;
	g->mm.visible_tiles = 11;
	g->mm.color_wall = 0xFFFFFF;
	g->mm.color_floor = 0x444444;
	g->mm.color_player = 0xFF0000;
	g->mm.color_direction = 0x00FF00;
	g->mm.color_border = 0xAAAAAA;
	g->mm.color_void = 0x000000;
}

void	draw_border(t_game *g, int x, int y)
{
	if ((x < g->mm.border || x >= (g->mm.width - g->mm.border))
		|| (y < g->mm.border || y >= (g->mm.height - g->mm.border)))
		pixel_put(&g->img, x, y, g->mm.color_border);
}

//a partir de la posicion del jugador, se desplaza segun el pixel del mapa dibujado, centrando la vista
//player_tile_x - centro del jugador
//x / mm.scale - qué tile estás dibujando en el minimapa
//mm.width / (2 * mm.scale) - cuánto te has alejado del centro hacia la izquierda
void	draw_tiles(t_game *g, int x, int y)
{
	char	cell;
	int		color;

	g->mm.player_tile_x = g->player.x / g->map.tile_size;
	g->mm.player_tile_y = g->player.y / g->map.tile_size;
	g->mm.map_x = g->mm.player_tile_x + (x / g->mm.scale - (g->mm.width
		/ g->mm.scale) / 2);
	g->mm.map_y = g->mm.player_tile_y + (y / g->mm.scale - (g->mm.height
		/  g->mm.scale) / 2);
	if (g->mm.map_x < 0 || g->mm.map_y < 0 || g->mm.map_x >= g->map.width
		|| g->mm.map_y >= g->map.height)
		return;
	if (g->map.grid[g->mm.map_y][g->mm.map_x])
		cell = g->map.grid[g->mm.map_y][g->mm.map_x];
	else
		cell = 'X';
	if (cell == '1')
		color = g->mm.color_wall;
	else if (cell == '0')
		color = g->mm.color_floor;
	else
		color = g->mm.color_void;
	pixel_put(&g->img, x, y, color);
}

void	draw_map_tiles(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->mm.height)
	{
		x = 0;
		while (x < g->mm.width)
		{
			draw_tiles(g, x, y);
			draw_border(g, x, y);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *g)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = g->mm.width / 2 + g->mm.scale / 2;
	y = g->mm.height / 2 + g->mm.scale / 2;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			pixel_put(&g->img,
				x + j,
				y + i,
				g->mm.color_player);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_game *g)
{
	float	x;
	float	y;
	float	i;

	x = g->mm.width / 2 + g->mm.scale / 2;
	y = g->mm.height / 2 + g->mm.scale / 2;

	i = 0;
	while (i < 40)
	{
		pixel_put(&g->img,
			x + g->player.dir_x * i,
			y + g->player.dir_y * i,
			g->mm.color_direction);
		i++;
	}
}

void	draw_minimap(t_game *g)
{
	draw_map_tiles(g);
	draw_player(g);
	draw_ray(g);
}
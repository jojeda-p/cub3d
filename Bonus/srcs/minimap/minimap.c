/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:15:16 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/11 12:38:20 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_tiles(t_game *g)
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

static void	clear_minimap(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->mm.height)
	{
		x = 0;
		while (x < g->mm.width)
		{
			pixel_put(&g->img, g->mm.margin_x + x, g->mm.margin_y
				+ y, g->mm.color_void);
			x++;
		}
		y++;
	}
}

static void	draw_player(t_game *g)
{
	int	cx;
	int	cy;
	int	i;
	int	j;

	cx = g->mm.margin_x + g->mm.inner_x;
	cy = g->mm.margin_y + g->mm.inner_y;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			pixel_put(&g->img, cx + j, cy + i, g->mm.color_player);
			j++;
		}
		i++;
	}
}

/* 	rx/y - pixel del centro del minimapa, donde se encuentra el personaje
	i - contador de pixeles avanzados del rayo en la direccion dir_x/y
	tile_x/y - posicion en mapa real donde se encuentr el punto actual del rayo
	*/
static void	draw_ray(t_game *g)
{
	float	rx;
	float	ry;
	int		tilex;
	int		tiley;
	float	i;

	rx = g->mm.margin_x + g->mm.inner_x;
	ry = g->mm.margin_y + g->mm.inner_y;
	g->mm.offset_x = (g->player.x / g->map.tile_size) * g->mm.scale;
	g->mm.offset_y = (g->player.y / g->map.tile_size) * g->mm.scale;
	i = 0;
	while (i < 80)
	{
		tilex = div_floor((int)(rx + g->player.dir_x * i) - g->mm.margin_x
				- g->mm.width / 2 + (int)g->mm.offset_x, g->mm.scale);
		tiley = div_floor((int)(ry + g->player.dir_y * i) - g->mm.margin_y
				- g->mm.height / 2 + (int)g->mm.offset_y, g->mm.scale);
		if (tilex >= 0 && tiley >= 0 && tilex < g->map.width
			&& tiley < g->map.height && g->map.grid[tiley][tilex] == '1')
			break ;
		pixel_put(&g->img, (int)(rx + g->player.dir_x * i),
			(int)(ry + g->player.dir_y * i), g->mm.color_direction);
		i++;
	}
}

void	draw_minimap(t_game *g)
{
	clear_minimap(g);
	draw_map_tiles(g);
	draw_player(g);
	draw_ray(g);
}

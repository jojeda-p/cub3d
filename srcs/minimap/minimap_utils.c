/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 13:59:07 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/11 12:30:52 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_border(t_game *g, int x, int y)
{
	if ((x < g->mm.border || x >= (g->mm.width - g->mm.border))
		|| (y < g->mm.border || y >= (g->mm.height - g->mm.border)))
		pixel_put(&g->img, g->mm.margin_x + x, g->mm.margin_y
			+ y, g->mm.color_border);
}

int	div_floor(int a, int b)
{
	int	result;
	int	remainder;

	result = a / b;
	remainder = a % b;
	if (remainder != 0 && (a < 0) != (b < 0))
		result--;
	return (result);
}

void	draw_tiles(t_game *g, int x, int y)
{
	char	cell;
	int		color;

	g->mm.offset_x = (g->player.x / g->map.tile_size) * g->mm.scale;
	g->mm.offset_y = (g->player.y / g->map.tile_size) * g->mm.scale;
	g->mm.map_x = div_floor(x - g->mm.width / 2
			+ (int)g->mm.offset_x, g->mm.scale);
	g->mm.map_y = div_floor(y - g->mm.height / 2
			+ (int)g->mm.offset_y, g->mm.scale);
	if (g->mm.map_x < 0 || g->mm.map_y < 0 || g->mm.map_x >= g->map.width
		|| g->mm.map_y >= g->map.height)
		return ;
	cell = g->map.grid[g->mm.map_y][g->mm.map_x];
	if (cell == '1')
		color = g->mm.color_wall;
	else if (cell == '0')
		color = g->mm.color_floor;
	else
		color = g->mm.color_void;
	pixel_put(&g->img, g->mm.margin_x + x, g->mm.margin_y + y, color);
}

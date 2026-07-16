/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:23:23 by josu              #+#    #+#             */
/*   Updated: 2026/07/16 16:02:07 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_door_color(t_game *g, int i, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	color;
	unsigned char	*pixel;
	int				j;

	if (tex_x < 0 || tex_x >= g->door[i].tex.width || tex_y < 0
		|| tex_y >= g->door[i].tex.height)
		return (0);
	offset = tex_y * g->door[i].tex.line_len
		+ tex_x * (g->door[i].tex.bpp / 8);
	pixel = (unsigned char *)g->door[i].tex.addr + offset;
	if ((g->door[i].tex.bpp / 8) == 4)
		color = *(unsigned int *)pixel;
	else
	{
		color = 0;
		j = 0;
		while (j < (g->door[i].tex.bpp / 8))
		{
			color |= ((unsigned int)pixel[j]) << (8 * j);
			j++;
		}
	}
	color = ft_fog(color, g->door[i].perp_dist);
	return ((int)color);
}

static void	draw_door_loop(t_game *g, int column, int i)
{
	int	y;
	int	color;

	y = g->door[i].draw_start;
	while (y <= g->door[i].draw_end)
	{
		g->door[i].tex_y = (int)g->door[i].tex_pos;
		if (g->door[i].tex_y < 0)
			g->door[i].tex_y = 0;
		if (g->door[i].tex_y >= g->door[i].tex.height)
			g->door[i].tex_y = g->door[i].tex.height - 1;
		color = get_door_color(g, i, g->door[i].tex_x,
				g->door[i].tex_y);
		pixel_put(&g->img, column, y, color);
		g->door[i].tex_pos += g->door[i].step;
		y++;
	}
}

void	draw_door_column(t_game *g, int column, int i)
{
	if (g->door[i].line_height <= 0 || g->door[i].tex.height <= 0)
		return ;
	g->door[i].step = (double)g->door[i].tex.height
		/ g->door[i].line_height;
	g->door[i].tex_pos = (g->door[i].draw_start
			- g->config.height / 2
			+ g->door[i].line_height / 2) * g->door[i].step;
	draw_door_loop(g, column, i);
	g->ray.z_buf[column] = g->door[i].perp_dist;
}

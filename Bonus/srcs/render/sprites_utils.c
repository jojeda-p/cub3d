/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:31:27 by josu              #+#    #+#             */
/*   Updated: 2026/07/05 18:05:02 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	get_sprite_tex_x(t_game *g, int x, int i)
{
	int	tex_x;
	int	d;

	d = x - (g->sprite[i].screen_x - g->sprite[i].width / 2);
	tex_x = d * g->sprite[i].frames[g->sprite[i].current_frame].width
		/ g->sprite[i].width;
	return (tex_x);
}

int	get_sprite_tex_y(t_game *g, int y, int i)
{
	int	tex_y;
	int	d;

	d = y - g->sprite[i].draw_start_y;
	tex_y = d * g->sprite[i].frames[g->sprite[i].current_frame].height
		/ g->sprite[i].height;
	return (tex_y);
}

void	update_sprite_animation(t_game *g)
{
	int	i;

	g->config.anim_speed = 10;
	g->config.frame_counter++;
	if (g->config.frame_counter < g->config.anim_speed)
		return ;
	g->config.frame_counter = 0;
	i = 0;
	while (i < g->config.sprite)
	{
		g->sprite[i].current_frame = (g->sprite[i].current_frame + 1)
			% g->sprite[i].num_frames;
		i++;
	}
}

void	check_sprite_pickup(t_game *g)
{
	int		i;
	double	dist;
	double	pickup_rad;
	int		tile_x;
	int		tile_y;

	pickup_rad = 50;
	i = 0;
	while (i < g->config.sprite)
	{
		if (!g->sprite[i].collected)
		{
			dist = sqrt(g->sprite[i].distance);
			if (dist < pickup_rad)
			{
				g->sprite[i].collected = 1;
				g->config.sprite_counter++;
				tile_x = (int)(g->sprite[i].x / g->map.tile_size);
				tile_y = (int)(g->sprite[i].y / g->map.tile_size);
				g->map.grid[tile_y][tile_x] = '0';
			}
		}
		i++;
	}
}

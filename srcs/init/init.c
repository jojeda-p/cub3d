/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:05:46 by julepere          #+#    #+#             */
/*   Updated: 2026/06/11 13:57:58 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_minimap(t_game *g)
{
	g->mm.width = g->config.width / 5;
	g->mm.height = g->config.height / 5;
	g->mm.margin_x = 20;
	g->mm.margin_y = 20;
	g->mm.border = 5;
	g->mm.scale = 30;
	g->mm.visible_tiles = 11;
	g->mm.color_wall = 0xFFFFFF;
	g->mm.color_floor = 0x444444;
	g->mm.color_player = 0xFF0000;
	g->mm.color_direction = 0x00FF00;
	g->mm.color_border = 0xAAAAAA;
	g->mm.color_void = 0x000000;
	g->mm.inner_x = g->mm.border + (g->mm.width - 2 * g->mm.border) / 2;
	g->mm.inner_y = g->mm.border + (g->mm.height - 2 * g->mm.border) / 2;
}

void	init_game(t_game *g)
{
	*g = (t_game){0};
	g->config.width = 1500;
	g->config.height = 1000;
	g->camera.fov = 75.0;
	g->camera.sensitivity = 0.0012;
	g->camera.last_mouse_x = -1;
	g->player.rot_speed = 0.03;
	g->player.accel = 0.15;
	g->player.max_speed    = g->player.walk_speed;

	g->camera.fov        = 75.0;
	g->camera.walk_fov   = 75.0;
	g->camera.sprint_fov = 80.0;
	
	g->player.force    = 80.0;
	g->player.mass     = 80.0;
	g->player.friction = 0.21;
	g->player.walk_speed   = 3.5;
	g->player.sprint_speed = 6.5;


	init_minimap(g);
}

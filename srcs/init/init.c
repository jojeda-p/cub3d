/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:05:46 by julepere          #+#    #+#             */
/*   Updated: 2026/06/04 13:39:49 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *g)
{
	*g = (t_game){0};
	g->config.width         = 1500;
	g->config.height        = 1000;
	g->config.floor_color   = 0x3B2F2F;
	g->config.ceiling_color = 0x87CEEB;
	g->camera.fov           = 75.0;
	g->camera.sensitivity   = 0.0012;
	g->camera.last_mouse_x  = -1;
	g->player.move_speed    = 0.05;
	g->player.rot_speed     = 0.03;
}
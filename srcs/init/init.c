/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:05:46 by julepere          #+#    #+#             */
/*   Updated: 2026/06/05 12:43:11 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *g)
{
	*g = (t_game){0};
	g->config.width = 1500;
	g->config.height = 1000;
	g->camera.fov  = 75.0;
	g->camera.sensitivity = 0.0012;
	g->camera.last_mouse_x = -1;
	g->player.move_speed = 0.05;
	g->player.rot_speed = 0.03;
	g->player.accel = 0.15;
	g->player.friction = 0.85;
	g->player.max_speed = 4.0;
}
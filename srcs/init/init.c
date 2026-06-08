/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:05:46 by julepere          #+#    #+#             */
/*   Updated: 2026/06/08 17:11:13 by julepere         ###   ########.fr       */
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
	g->player.rot_speed = 0.03;
	g->player.accel = 0.15;
	g->player.max_speed = 4.0;
	g->player.inertia = 1.0;
	g->player.mass = 80.0;
	g->player.move_speed = 4.0;
}
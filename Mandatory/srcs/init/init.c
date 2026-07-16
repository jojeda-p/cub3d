/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:05:46 by julepere          #+#    #+#             */
/*   Updated: 2026/07/16 13:14:24 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

void	init_game(t_game *g)
{
	*g = (t_game){0};
	g->config.width = 1000;
	g->config.height = 500;
	g->camera.fov = 75.0;
	g->player.rot_speed = 0.03;
	g->player.accel = 1;
	g->ray.z_buf = malloc(sizeof(double) * g->config.width);
}

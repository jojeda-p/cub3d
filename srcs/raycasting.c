/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:34:06 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/05/28 16:58:29 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>


/*cam es perpendicular a dir, por eso -dir_y e dir_x (rotación 90°)
scale determina el campo de visión (cuanto más grande, más FOV)*/
void	init_raycasting(t_game *g)
{
	double	fov;// FOV en grados
	double	fov_rad;// FOV en radianes
	double	scale;// Escala del plano

	g->dir_x = cos(g->player_dir);
	g->dir_y = sin(g->player_dir);
	fov = 60.0;
	fov_rad = fov * M_PI / 180.0;
	scale = tan(fov_rad / 2.0);
	g->cam_x = -g->dir_y * scale;
	g->cam_y = g->dir_x * scale;
}

void	render_raycasting(t_game *g)
{
	double	pos_x;
	double	pos_y;

	pos_x = g->player_x / g->map.tile_size;
	pos_y = g->player_y / g->map.tile_size;
	/*construimos un vector de rayo para cada columna*/
	while ()
	{
		
	}
}

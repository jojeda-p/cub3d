/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:34:06 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/05/29 13:39:20 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


/*cam es perpendicular a dir, por eso -dir_y e dir_x (rotación 90°)
scale determina el campo de visión (cuanto más grande, más FOV)
Inicializa la dirección del jugador y el plano de cámara (FOV) calculando
 dir_x, dir_y, cam_x y cam_y a partir del ángulo del jugador*/
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

/* convierte el valor de la columna dependiendo el ancho  en un numero entre -1 y 1*/
double	calculate_camera_x(int column, int width)
{
	double	camera_x;
	double	d_column;
	double	d_width;
	
	if (width <= 0)
		return (0);
	d_column = (double)column;
	d_width = (double)width;
	camera_x = d_column / d_width * 2 - 1;
	return (camera_x);
}

void	calculate_ray_dir(t_game *g)
{
	g->ray.ray_dir_x = g->dir_x + g->cam_x * g->ray.camera_x;
	g->ray.ray_dir_y = g->dir_y + g->cam_y * g->ray.camera_x;
}

void	init_ray_values(t_game *g)
{
	
}

/*Procesamos una columna
Calculamos un rayo
Lo avanzamos hasta chocar con una pared
Calculamos cómo se ve esa pared
La dibujamos
Pasamos a la siguiente columna*/
/* calcular camera_x para esta columna */
/* calcular la direccion del rayo */
/* inicializar datos del rayo */
/* ejecutar DDA hasta chocar con una pared */
/* calcular la altura de la pared y los limites de dibujo */
/* dibujar la columna en la imagen */
void	render_raycasting(t_game *g)
{
	int	column;

	column = 0;
	while (column < g->width)
	{
		g->ray.camera_x = calculate_camera_x(column, g->width);
		calculate_ray_dir(g);
		init_ray_values(g);
		column++;
	}
}

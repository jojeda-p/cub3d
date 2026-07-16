/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:56:03 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 13:37:25 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/*cam es perpendicular a dir, por eso -dir_y e dir_x (rotación 90°)
scale determina el campo de visión (cuanto más grande, más FOV)
Inicializa la dirección del jugador y el plano de cámara (FOV) calculando
 dir_x, dir_y, cam_x y cam_y a partir del ángulo del jugador*/
void	init_raycasting(t_game *g)
{
	double	fov_rad;
	double	scale;

	g->player.dir_x = cos(g->player.dir);
	g->player.dir_y = sin(g->player.dir);
	fov_rad = g->camera.fov * M_PI / 180.0;
	scale = tan(fov_rad / 2.0);
	g->camera.plane_x = -g->player.dir_y * scale;
	g->camera.plane_y = g->player.dir_x * scale;
}

/* convierte el valor de la columna dependiendo el ancho  en un
 numero entre -1 y 1*/
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

/* Inicializa TODO para cada rayo:

Dirección del rayo (ray_dir_x, ray_dir_y)
Posición inicial en el mapa
Delta distances→cómo de lejos está el siguiente gridline(vertical u horizontal)
Side distances → distancia hasta el próximo gridline
Steps → hacia dónde avanzar (-1 o 1)*/
void	init_ray_values(t_game *g)
{
	g->ray.ray_dir_x = g->player.dir_x + g->camera.plane_x * g->ray.camera_x;
	g->ray.ray_dir_y = g->player.dir_y + g->camera.plane_y * g->ray.camera_x;
	g->ray.map_x = (int)(g->player.x / g->map.tile_size);
	g->ray.map_y = (int)(g->player.y / g->map.tile_size);
	if (g->ray.ray_dir_x == 0)
		g->ray.delta_dist_x = INFINITY;
	else
		g->ray.delta_dist_x = fabs(1.0 / g->ray.ray_dir_x);
	if (g->ray.ray_dir_y == 0)
		g->ray.delta_dist_y = INFINITY;
	else
		g->ray.delta_dist_y = fabs(1.0 / g->ray.ray_dir_y);
	init_ray_values2(g);
}

void	init_ray_values2(t_game *g)
{
	if (g->ray.ray_dir_x < 0)
		g->ray.step_x = -1;
	else
		g->ray.step_x = 1;
	if (g->ray.ray_dir_y < 0)
		g->ray.step_y = -1;
	else
		g->ray.step_y = 1;
	if (g->ray.step_x == -1)
		g->ray.side_dist_x = ((g->player.x / g->map.tile_size) - g->ray.map_x)
			* g->ray.delta_dist_x;
	else
		g->ray.side_dist_x = (g->ray.map_x + 1.0
				- (g->player.x / g->map.tile_size)) * g->ray.delta_dist_x;
	if (g->ray.step_y == -1)
		g->ray.side_dist_y = ((g->player.y / g->map.tile_size) - g->ray.map_y)
			* g->ray.delta_dist_y;
	else
		g->ray.side_dist_y = (g->ray.map_y + 1.0
				- (g->player.y / g->map.tile_size)) * g->ray.delta_dist_y;
	g->ray.hit = 0;
	g->ray.side = 0;
}

/*escribe un color (ARGB) en la posición (x,y) dentro del buffer de mlx
 usando addr, bpp y line_len esta funcion solo solo coloca un valor de color
  en una posición exacta de memoria quedespues render_g mandara a la pantalla
 dst es la dirección de memoria donde se va a guardar un pixel concreto*/
void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

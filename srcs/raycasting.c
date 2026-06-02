/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:34:06 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/02 15:49:16 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	draw_wall_column(t_game *g, int column, t_tex texture)
{
	int	y;
	/* int	tex_x; */
	int	tex_y;

	if (column < 0 || column >= g->width)
		return;
	if (g->ray.draw_start > g->ray.draw_end)
		return;
	y = g->ray.draw_start;
	/* tex_x = get_tex_x(g, texture); */
	while (y <= g->ray.draw_end)
	{
		tex_y = (int)((y - g->ray.draw_start) * (double)texture.height / g->ray.line_height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture.height)
			tex_y = texture.height - 1;
		pixel_put(&g->img, column, y, 0x000080);
		/* pixel_put(&g->img, column, y, get_tex_color(texture, tex_x, tex_y)); */
		y++;
	}
}

/*Esta funcion calcula 3 datos principales

Distancia perpendicular a la pared(evita ojo de pez)
	map_x, map_y son la celda donde terminó el DDA
	step_x, step_y dicen hacia qué lado avanzaba el rayo
	ray_dir_x, ray_dir_y es la dirección del rayo
Altura de la pared en pantalla
Inicio y fin de la columna a dibujar
*/
void	calculate_wall_projection(t_game *g)
{
	if (g->ray.side == 0)
		g->ray.perp_dist = (g->ray.map_x - (g->player_x / g->map.tile_size) + (1.0 - (double)g->ray.step_x) / 2.0) / g->ray.ray_dir_x;
	else
		g->ray.perp_dist = (g->ray.map_y - (g->player_y / g->map.tile_size) + (1.0 - (double)g->ray.step_y) / 2.0) / g->ray.ray_dir_y;
	if (!isfinite(g->ray.perp_dist) || g->ray.perp_dist <= 0.0)
		g->ray.perp_dist = 1e-6;
	g->ray.line_height = (int)((double)g->height / g->ray.perp_dist);
	g->ray.draw_start = (int)(-((double)g->ray.line_height) / 2.0 + (double)g->height / 2.0);
	g->ray.draw_end   = (int)(((double)g->ray.line_height) / 2.0 + (double)g->height / 2.0);
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	if (g->ray.draw_end >= g->height)
		g->ray.draw_end = g->height - 1;
}

void	dda_loop(t_game *g)
{
	while (g->ray.hit == 0)
	{
		if (g->ray.side_dist_x < g->ray.side_dist_y)//golpeo lado vertical
		{
			g->ray.side_dist_x = g->ray.delta_dist_x + g->ray.side_dist_x;
			g->ray.map_x = g->ray.step_x + g->ray.map_x;
			g->ray.side = 0;
		}
		else
		{
			g->ray.side_dist_y = g->ray.delta_dist_y + g->ray.side_dist_y;
			g->ray.map_y = g->ray.step_y + g->ray.map_y;
			g->ray.side = 1;
		}
		if (g->ray.map_x < 0 || g->ray.map_x >= g->map.width ||
   			g->ray.map_y < 0 || g->ray.map_y >= g->map.height)
    		g->ray.hit = 1;
		else if (g->map.grid[g->ray.map_y][g->ray.map_x] == '1')
			g->ray.hit = 1;
	}
	
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
	int		column;
	t_tex	texture;

	column = 0;
	while (column < g->width)
	{
		g->ray.camera_x = calculate_camera_x(column, g->width);
		init_ray_values(g);
		dda_loop(g);
		texture = get_wall_texture(g);
		calculate_wall_projection(g);
		draw_wall_column(g, column, texture);
		column++;
	}
}

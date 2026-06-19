/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:43:19 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/19 14:11:34 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

static void	order_sprites(t_game *g)//falta hacer que se salte los recolectados
{
	int			i;
	double		dx;
	double		dy;
	t_sprite	aux;

	i = 0;
	while (i < g->config.sprite)
	{
		dx = g->sprite[i].x - g->player.x;
		dy = g->sprite[i].y - g->player.y;
		g->sprite[i].distance = dx * dx + dy * dy;
		i++;
	}
	i = 0;
	while (i < g->config.sprite - 1)
	{
		if (g->sprite[i].distance < g->sprite[i + 1].distance)
		{
			aux = g->sprite[i];
			g->sprite[i] = g->sprite[i + 1];
			g->sprite[i + 1] = aux;
			i = -1;
		}
		i++;
	}
}

static void	calculate_sprite_2(t_game *g, int i)
{
	double	v_offset;

	v_offset = 200 / g->sprite[i].transform_y;
	g->sprite[i].draw_start_y = -g->sprite[i].height
		/ 2 + g->config.height / 2 + (int)v_offset;
	g->sprite[i].draw_end_y   =  g->sprite[i].height
		/ 2 + g->config.height / 2 + (int)v_offset;
	if (g->sprite[i].draw_start_y < 0)
		g->sprite[i].draw_start_y = 0;
	if (g->sprite[i].draw_end_y >= g->config.height)
		g->sprite[i].draw_end_y = g->config.height - 1;
	g->sprite[i].draw_start_x = -g->sprite[i].width
		/ 2 + g->sprite[i].screen_x;
	g->sprite[i].draw_end_x   =  g->sprite[i].width
		/ 2 + g->sprite[i].screen_x;
	if (g->sprite[i].draw_start_x < 0)
		g->sprite[i].draw_start_x = 0;
	if (g->sprite[i].draw_end_x >= g->config.width)
		g->sprite[i].draw_end_x = g->config.width - 1;
}


/*dx y dy — vector desde el jugador hasta el sprite en unidades del mundo.
inv_det — el determinante inverso de la matriz de cámara.
Tu cámara tiene dos vectores: dir (hacia donde miras) y plane 
(el plano perpendicular que define el FOV).*/
static void	calculate_sprite(t_game *g, int i)
{
	double  dx;
    double  dy;
    double  inv_det;
	
	dx = (g->sprite[i].x - g->player.x) / g->map.tile_size;
	dy = (g->sprite[i].y - g->player.y) / g->map.tile_size;
	inv_det = 1.0 / (g->camera.plane_x * g->player.dir_y - g->player.dir_x
		* g->camera.plane_y);
	g->sprite[i].transform_x = inv_det * (g->player.dir_y * dx
		- g->player.dir_x * dy);
	g->sprite[i].transform_y = inv_det * (-g->camera.plane_y * dx
		+ g->camera.plane_x * dy);
	if (g->sprite[i].transform_y <= 0)
		return ;
	g->sprite[i].screen_x = (int)(g->config.width / 2
    	* (1 + g->sprite[i].transform_x / g->sprite[i].transform_y));
	g->sprite[i].height = abs((int)(g->config.height
		/ g->sprite[i].transform_y)) * 0.3;
	g->sprite[i].width  = abs((int)(g->config.width
		/ g->sprite[i].transform_y)) * 0.3;
	calculate_sprite_2(g, i);
}

static void	draw_sprite(t_game *g, int i)
{
	int x;
    int y;
    int tex_x;
    int tex_y;
	int	color;

    if (g->sprite[i].transform_y <= 0)
        return ;
    x = g->sprite[i].draw_start_x;
	while (x < g->sprite[i].draw_end_x)
    {
        if (g->sprite[i].transform_y < g->ray.z_buf[x])
        {
			tex_x = get_sprite_tex_x(g, x, i);
            y = g->sprite[i].draw_start_y;
            while (y < g->sprite[i].draw_end_y)
            {
				tex_y = get_sprite_tex_y(g, y, i);
				color = get_sprite_color(g, i, tex_x, tex_y);
				if (color != 0xae17cc)
					pixel_put(&g->img, x, y, color);
                y++;
            }
        }
        x++;
    }
}

void	render_sprites(t_game *g)
{
	int	i;

	order_sprites(g);
	i = 0;
	while (i < g->config.sprite)
	{
		check_sprite_pickup(g);
		if (!g->sprite[i].collected)
		{
			calculate_sprite(g, i);
			draw_sprite(g, i);
		}
		i++;
	}
}

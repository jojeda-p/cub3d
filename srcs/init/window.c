/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 17:38:27 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/15 14:32:28 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"

/*Dibujar en el buffer de la imagen todo el frame: cielo, suelo, muros
(raycasting), texturas y sprites, y finalmente enviar la imagen a la ventana*/
int	render_g(t_game	*g)
{
	if (g->state == STATE_PAUSE)
		return (render_pause(g));
	if (g->state == STATE_END)
		return (render_end(g));
	update_player(g);
	update_sprite_animation(g);
	update_weapon(g);
	render_raycasting(g);
	render_weapon(g);
	draw_minimap(g);
	draw_crosshair(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	draw_progress(g);
	check_game_end(g);
	return (0);
}

/*
crear imagen en RAM
guardar puntero de la imagen
ademas rellena automaticamente las variales de img -> bbp, line_len y endian
*/
static int	init_image(t_game *g)
{
	g->img.img = mlx_new_image(g->mlx, g->config.width, g->config.height);
	if (!g->img.img)
		return (-1);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	return (0);
}

int	init_window(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (-1);
	g->win = mlx_new_window(g->mlx, g->config.width, g->config.height, "cub3d");
	if (!g->win)
		return (free_game(g), -1);
	if (init_image(g) == -1)
		return (free_game(g), -1);
	if (load_textures(g) != 0)
		return (free_game(g), -1);
	if (load_sprite_textures(g) != 0)
		return (free_game(g), -1);
	if (load_weapon_anims(g) != 0)
		return (free_game(g), -1);
	mlx_loop_hook(g->mlx, render_g, g);
	mlx_hook(g->win, 17, 0, close_window, g);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 4, 1L << 2, mouse_press, g);
	mlx_hook(g->win, 5, 1L << 3, mouse_release, g);
	mlx_loop(g->mlx);
	return (0);
}

int	close_window(t_game *g)
{
	free_game(g);
	exit(0);
	return (0);
}

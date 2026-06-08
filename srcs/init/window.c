/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 17:38:27 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/08 14:03:19 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include "mlx.h"

/*escribe un color (ARGB) en la posición (x,y) dentro del buffer de mlx
 usando addr, bpp y line_len esta funcion solo solo coloca un valor de color
  en una posición exacta de memoria quedespues render_g mandara a la pantalla
 dst es la dirección de memoria donde se va a guardar un pixel concreto*/
void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	if (!img || !img->addr || x < 0 || y < 0)
		return ;
	dst = img->addr + (y *  img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

/*Dibujar en el buffer de la imagen todo el frame: cielo, suelo, muros
(raycasting), texturas y sprites, y finalmente enviar la imagen a la ventana*/
int	render_g(t_game	*g)
{
	int	x;
	int	y;

	update_player(g);
	y = 0;
	while (y < g->config.height)
	{
		x = 0;
		while (x < g->config.width)
		{
			if (y < g->config.height / 2)
				pixel_put(&g->img, x, y, g->config.ceiling_color);
			else
				pixel_put(&g->img, x, y, g->config.floor_color);
			x++;
		}
		y++;
	}
	render_raycasting(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}

static int	init_image(t_game *g)
{
	g->img.img = mlx_new_image(g->mlx, g->config.width, g->config.height); //crear imagen en RAM
	if (!g->img.img)
		return (-1);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
		&g->img.line_len, &g->img.endian);// guardar puntero de la imagen
	return (0);//ademas rellena automaticamente las variales de img -> bbp,
	// line_len y endian
}

int	init_window(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (-1);
	g->win = mlx_new_window(g->mlx, g->config.width, g->config.height, "cub3d");
	if (!g->win)
		return (-1);
	if (init_image(g) == -1)
		return (-1);
	load_textures(g);
	mlx_loop_hook(g->mlx, render_g, g);
	mlx_hook(g->win, 17, 0, close_window, g);
	mlx_hook(g->win, 2, 1L<<0, key_press, g);
	mlx_hook(g->win, 3, 1L<<1, key_release, g);
	mlx_loop(g->mlx);
	return (0);
}

int	close_window(t_game *g)
{
	if (g && g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	exit(0);
	return (0);
}


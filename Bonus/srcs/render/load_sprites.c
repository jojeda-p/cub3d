/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:10:50 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include <stdio.h>

static void	destroy_loaded_frames(t_game *g, t_sprite *sprite, int loaded)
{
	int	i;

	i = 0;
	while (i < loaded)
	{
		if (sprite->frames[i].img)
		{
			mlx_destroy_image(g->mlx, sprite->frames[i].img);
			sprite->frames[i].img = NULL;
			sprite->frames[i].addr = NULL;
		}
		i++;
	}
}

static int	load_sprite_frames(t_game *g, int i)
{
	int	j;

	j = 0;
	while (j < g->sprite[i].num_frames)
	{
		g->sprite[i].frames[j].img = mlx_xpm_file_to_image(g->mlx,
				g->sprite[i].frames[j].path, &g->sprite[i].frames[j].width,
				&g->sprite[i].frames[j].height);
		if (!g->sprite[i].frames[j].img)
			return (destroy_loaded_frames(g, &g->sprite[i], j), 1);
		g->sprite[i].frames[j].addr = mlx_get_data_addr(
				g->sprite[i].frames[j].img, &g->sprite[i].frames[j].bpp,
				&g->sprite[i].frames[j].line_len,
				&g->sprite[i].frames[j].endian);
		if (!g->sprite[i].frames[j].addr)
		{
			mlx_destroy_image(g->mlx, g->sprite[i].frames[j].img);
			g->sprite[i].frames[j].img = NULL;
			return (destroy_loaded_frames(g, &g->sprite[i], j), 1);
		}
		g->sprite[i].collected = 0;
		j++;
	}
	return (0);
}

int	load_sprite_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->config.sprite)
	{
		if (load_sprite_frames(g, i))
			return (1);
		i++;
	}
	return (0);
}

static void	cast_texture(t_game *g, int i)
{
	g->sprite[i].frames[0].path = "assets/gifs/ammo/frame-01.xpm";
	g->sprite[i].frames[1].path = "assets/gifs/ammo/frame-02.xpm";
	g->sprite[i].frames[2].path = "assets/gifs/ammo/frame-03.xpm";
	g->sprite[i].frames[3].path = "assets/gifs/ammo/frame-04.xpm";
	g->sprite[i].frames[4].path = "assets/gifs/ammo/frame-05.xpm";
	g->sprite[i].frames[5].path = "assets/gifs/ammo/frame-06.xpm";
	g->sprite[i].frames[6].path = "assets/gifs/ammo/frame-07.xpm";
	g->sprite[i].frames[7].path = "assets/gifs/ammo/frame-08.xpm";
	g->sprite[i].frames[8].path = "assets/gifs/ammo/frame-09.xpm";
	g->sprite[i].frames[9].path = "assets/gifs/ammo/frame-10.xpm";
	g->sprite[i].frames[10].path = "assets/gifs/ammo/frame-11.xpm";
	g->sprite[i].frames[11].path = "assets/gifs/ammo/frame-12.xpm";
	g->sprite[i].frames[12].path = "assets/gifs/ammo/frame-13.xpm";
	g->sprite[i].frames[13].path = "assets/gifs/ammo/frame-14.xpm";
	g->sprite[i].frames[14].path = "assets/gifs/ammo/frame-15.xpm";
	g->sprite[i].frames[15].path = "assets/gifs/ammo/frame-16.xpm";
	g->sprite[i].num_frames = 16;
	g->sprite[i].current_frame = 0;
}

void	load_sprite(t_game *g)
{
	int	i;

	if (g->config.sprite == 0)
		return ;
	i = 0;
	while (i < g->config.sprite)
	{
		cast_texture(g, i);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:17:15 by josu              #+#    #+#             */
/*   Updated: 2026/07/16 15:41:56 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include "mlx.h"

static void	destroy_tex(t_game *g, t_tex *tex)
{
	if (g->mlx && tex->img)
		mlx_destroy_image(g->mlx, tex->img);
	tex->img = NULL;
	tex->addr = NULL;
}

static void	free_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		destroy_tex(g, &g->tex[i]);
		free(g->tex[i].path);
		g->tex[i].path = NULL;
		i++;
	}
	destroy_tex(g, &g->pause_tex);
	destroy_tex(g, &g->end);
	if (g->mlx && g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	g->img.img = NULL;
	g->img.addr = NULL;
}

static void	free_sprites(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->sprite && i < g->config.sprite)
	{
		j = 0;
		while (j < g->sprite[i].num_frames)
		{
			if (g->mlx && g->sprite[i].frames[j].img)
				mlx_destroy_image(g->mlx,
					g->sprite[i].frames[j].img);
			g->sprite[i].frames[j].img = NULL;
			j++;
		}
		i++;
	}
	free(g->sprite);
	g->sprite = NULL;
}

static void	free_doors(t_game *g)
{
	int	i;

	i = 0;
	while (g->door && i < g->config.door)
	{
		if (g->mlx && g->door[i].tex.img)
			mlx_destroy_image(g->mlx, g->door[i].tex.img);
		g->door[i].tex.img = NULL;
		i++;
	}
	free(g->door);
	g->door = NULL;
}

static void	free_weapon(t_game *g)
{
	int	state;
	int	frame;

	state = 0;
	while (state < 9)
	{
		frame = 0;
		while (frame < g->weapon.frame_count[state])
		{
			if (g->mlx && g->weapon.frames[state]
				&& g->weapon.frames[state][frame].img)
				mlx_destroy_image(g->mlx,
					g->weapon.frames[state][frame].img);
			frame++;
		}
		free(g->weapon.frames[state]);
		g->weapon.frames[state] = NULL;
		g->weapon.frame_count[state] = 0;
		state++;
	}
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	free_textures(g);
	free_sprites(g);
	free_doors(g);
	free_weapon(g);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	g->win = NULL;
	if (g->map.grid)
		free_matrix(g->map.grid);
	g->map.grid = NULL;
	free(g->ray.z_buf);
	g->ray.z_buf = NULL;
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	g->mlx = NULL;
}

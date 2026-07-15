/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:17:15 by josu              #+#    #+#             */
/*   Updated: 2026/07/15 14:20:30 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include "mlx.h"

static void	free_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->tex[i].img)
			mlx_destroy_image(g->mlx, g->tex[i].img);
		i++;
	}
	if (g->pause_tex.img)
		mlx_destroy_image(g->mlx, g->pause_tex.img);
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	i = 0;
	while (i < 4)
	{
		free(g->tex[i].path);
		g->tex[i].path = NULL;
		i++;
	}
}

static void	free_sprites(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->config.sprite)
	{
		j = 0;
		while (j < g->sprite[i].num_frames)
		{
			if (g->sprite[i].frames[j].img)
				mlx_destroy_image(g->mlx, g->sprite[i].frames[j].img);
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
	while (i < g->config.door)
	{
		if (g->door[i].tex.img)
			mlx_destroy_image(g->mlx, g->door[i].tex.img);
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
			if (g->weapon.frames[state]
				&& g->weapon.frames[state][frame].img)
				mlx_destroy_image(g->mlx,
					g->weapon.frames[state][frame].img);
			frame++;
		}
		free(g->weapon.frames[state]);
		g->weapon.frames[state] = NULL;
		state++;
	}
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	if (g->mlx)
	{
		free_textures(g);
		if (g->sprite)
			free_sprites(g);
		if (g->door)
			free_doors(g);
		free_weapon(g);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
	}
	if (g->map.grid)
		free_matrix(g->map.grid);
	if (g->end.img)
	{
		mlx_destroy_image(g->mlx, g->end.img);
		g->end.img = NULL;
	}
	free(g->ray.z_buf);
	g->ray.z_buf = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:17:15 by josu              #+#    #+#             */
/*   Updated: 2026/07/16 14:28:21 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include "mlx.h"

static void	free_images(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->mlx && g->tex[i].img)
			mlx_destroy_image(g->mlx, g->tex[i].img);
		g->tex[i].img = NULL;
		g->tex[i].addr = NULL;
		i++;
	}
	if (g->mlx && g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	g->img.img = NULL;
	g->img.addr = NULL;
}

static void	free_texture_paths(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(g->tex[i].path);
		g->tex[i].path = NULL;
		i++;
	}
}

void	free_game(t_game *g)
{
	if (!g)
		return ;
	free_images(g);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	g->win = NULL;
	free_texture_paths(g);
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

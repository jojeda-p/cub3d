/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:17:15 by josu              #+#    #+#             */
/*   Updated: 2026/07/16 13:13:16 by jojeda-p         ###   ########.fr       */
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

void	free_game(t_game *g)
{
	if (!g)
		return ;
	if (g->mlx)
	{
		free_textures(g);
		if (g->win)
			mlx_destroy_window(g->mlx, g->win);
	}
	if (g->map.grid)
		free_matrix(g->map.grid);
	free(g->ray.z_buf);
	g->ray.z_buf = NULL;
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

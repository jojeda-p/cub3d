/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:06:38 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdio.h>
#include <stdlib.h>

static int	init_sprite_door(t_game *g)
{
	int	i;

	g->sprite = malloc(sizeof(t_sprite) * g->config.sprite);
	if (!g->sprite && g->config.sprite > 0)
		return (1);
	g->door = malloc(sizeof(t_door) * g->config.door);
	if (!g->door && g->config.door > 0)
	{
		free(g->sprite);
		g->sprite = NULL;
		return (1);
	}
	i = 0;
	while (i < g->config.sprite)
	{
		g->sprite[i] = (t_sprite){0};
		i++;
	}
	i = 0;
	while (i < g->config.door)
	{
		g->door[i] = (t_door){0};
		i++;
	}
	return (0);
}

int	init_map(t_game *g)
{
	g->map.width = get_width(g);
	g->map.height = get_height(g);
	get_player(g);
	g->map.tile_size = 64;
	g->player.x = (g->player.x * g->map.tile_size);
	g->player.y = (g->player.y * g->map.tile_size);
	g->config.sprite = g->map.anim;
	g->config.door = g->map.door;
	if (init_sprite_door(g))
		return (1);
	g->config.sprite_counter = 0;
	return (0);
}

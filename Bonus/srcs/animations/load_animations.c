/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:13:53 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/15 15:17:40 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	init_frames_array(t_game *g, int state, int count)
{
	int	i;

	g->weapon.frames[state] = malloc(sizeof(t_frame) * count);
	if (!g->weapon.frames[state])
		return (1);
	i = 0;
	while (i < count)
	{
		g->weapon.frames[state][i] = (t_frame){0};
		i++;
	}
	g->weapon.frame_count[state] = count;
	return (0);
}

int	load_anim(t_game *g, int state, char *folder, int count)
{
	char	*base;
	char	*name;

	if (init_frames_array(g, state, count))
		return (1);
	name = get_name(folder);
	base = ft_strjoin(folder, "/");
	if (!base)
	{
		free(g->weapon.frames[state]);
		g->weapon.frames[state] = NULL;
		g->weapon.frame_count[state] = 0;
		return (1);
	}
	if (load_frames_loop(g, state, base, name))
	{
		free(base);
		return (1);
	}
	free(base);
	return (0);
}

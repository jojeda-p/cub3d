/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_logic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 15:31:31 by julepere          #+#    #+#             */
/*   Updated: 2026/07/15 13:10:46 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	weapon_loop_state(t_game *g)
{
	if (is_sprinting(g))
		return (SPRINT);
	return (IDLE);
}

void	advance_weapon_frame(t_game *g)
{
	int	count;

	count = g->weapon.frame_count[g->weapon.state];
	if (count <= 1)
		return ;
	g->weapon.tick++;
	if (g->weapon.tick < g->weapon.speed)
		return ;
	g->weapon.tick = 0;
	if (g->weapon.reversed)
	{
		if (g->weapon.current > 0)
			g->weapon.current--;
		else if (g->weapon.looping)
			g->weapon.current = count - 1;
	}
	else
	{
		if (g->weapon.current + 1 < count)
			g->weapon.current++;
		else if (g->weapon.looping)
			g->weapon.current = 0;
	}
}

int	weapon_frame_finished(t_game *g)
{
	int	count;

	count = g->weapon.frame_count[g->weapon.state];
	if (count <= 0)
		return (1);
	if (g->weapon.reversed)
		return (g->weapon.current <= 0);
	return (g->weapon.current >= count - 1);
}

void	start_blocking_state(t_game *g, int state)
{
	set_state(g, state, 0, 0);
	g->weapon.blocking = 1;
}

void	start_one_shot_state(t_game *g, int state)
{
	set_state(g, state, 0, 0);
	g->weapon.blocking = 1;
	g->weapon.next_state = weapon_loop_state(g);
}

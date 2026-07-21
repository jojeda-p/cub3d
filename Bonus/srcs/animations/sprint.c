/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:01:00 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	start_sprint_reverse(t_game *g, int next_state)
{
	int	last_frame;
	int	was_hidden;

	last_frame = g->weapon.frame_count[SPRINT] - 1;
	if (last_frame < 0)
		last_frame = 0;
	was_hidden = g->weapon.hidden;
	g->weapon.state = SPRINT;
	g->weapon.tick = 0;
	g->weapon.looping = 0;
	g->weapon.reversed = 1;
	g->weapon.blocking = 1;
	g->weapon.hidden = 0;
	g->weapon.next_state = next_state;
	if (was_hidden)
		g->weapon.current = last_frame;
	else if (g->weapon.current >= g->weapon.frame_count[SPRINT])
		g->weapon.current = last_frame;
}

void	enter_sprint_hold(t_game *g)
{
	int	last_frame;

	last_frame = g->weapon.frame_count[SPRINT] - 1;
	if (last_frame < 0)
		last_frame = 0;
	g->weapon.state = SPRINT;
	g->weapon.current = last_frame;
	g->weapon.tick = 0;
	g->weapon.looping = 0;
	g->weapon.reversed = 0;
	g->weapon.blocking = 0;
	g->weapon.hidden = 1;
	g->weapon.next_state = weapon_loop_state(g);
}

void	start_sprint_enter(t_game *g)
{
	set_state(g, SPRINT, 0, 0);
	g->weapon.blocking = 1;
	g->weapon.next_state = weapon_loop_state(g);
}

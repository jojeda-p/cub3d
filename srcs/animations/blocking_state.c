/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocking_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:06:42 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/15 13:15:18 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	finish_blocking_sprint(t_game *g)
{
	if (g->weapon.reversed)
	{
		if (g->weapon.next_state == RELOAD || g->weapon.next_state == AIM_IN
			|| g->weapon.next_state == AIM_OUT || g->weapon.next_state == SHOOT
			|| g->weapon.next_state == SPECIAL)
		{
			start_blocking_state(g, g->weapon.next_state);
			return ;
		}
		if (is_sprinting(g))
			enter_sprint_hold(g);
		else
			set_state(g, IDLE, 1, 0);
		return ;
	}
	if (is_sprinting(g))
		enter_sprint_hold(g);
	else
		start_sprint_reverse(g, weapon_loop_state(g));
}

static void	finish_blocking_non_sprint(t_game *g)
{
	int	state;

	state = g->weapon.state;
	if (state == AIM_IN)
	{
		set_state(g, AIM, 1, 0);
		return ;
	}
	if (state == AIM_OUT || state == RELOAD || state == SHOOT
		|| state == SPECIAL)
	{
		if (is_sprinting(g))
			enter_sprint_hold(g);
		else
			set_state(g, IDLE, 1, 0);
		return ;
	}
}

void	finish_blocking_state(t_game *g)
{
	int	state;

	state = g->weapon.state;
	g->weapon.blocking = 0;
	if (state == SPRINT)
	{
		finish_blocking_sprint(g);
		return ;
	}
	finish_blocking_non_sprint(g);
}

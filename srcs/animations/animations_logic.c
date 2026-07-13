/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_logic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 15:31:31 by julepere          #+#    #+#             */
/*   Updated: 2026/07/13 14:17:05 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	weapon_loop_state(t_game *g)
{
	if (is_sprinting(g))
		return (SPRINT);
	return (IDLE);
}

static void	advance_weapon_frame(t_game *g)
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

static int	weapon_frame_finished(t_game *g)
{
	int	count;

	count = g->weapon.frame_count[g->weapon.state];
	if (count <= 0)
		return (1);
	if (g->weapon.reversed)
		return (g->weapon.current <= 0);
	return (g->weapon.current >= count - 1);
}

static void	start_blocking_state(t_game *g, int state)
{
	set_state(g, state, 0, 0);
	g->weapon.blocking = 1;
}

static void	start_one_shot_state(t_game *g, int state)
{
	set_state(g, state, 0, 0);
	g->weapon.blocking = 1;
	g->weapon.next_state = weapon_loop_state(g);
}

static void	start_sprint_enter(t_game *g)
{
	set_state(g, SPRINT, 0, 0);
	g->weapon.blocking = 1;
	g->weapon.next_state = weapon_loop_state(g);
}

static void	enter_sprint_hold(t_game *g)
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

static void	start_sprint_reverse(t_game *g, int next_state)
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

static void	finish_blocking_state(t_game *g)
{
	int	state;

	state = g->weapon.state;
	g->weapon.blocking = 0;
	if (state == SPRINT)
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
		return ;
	}
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

void	update_weapon(t_game *g)
{
	int	state;

	state = g->weapon.state;
	if (g->weapon.blocking)
	{
		advance_weapon_frame(g);
		if (weapon_frame_finished(g))
			finish_blocking_state(g);
		return ;
	}
	if (g->input.special && state != SPECIAL)
	{
		g->input.special = 0;
		if (state == SPRINT)
			start_sprint_reverse(g, SPECIAL);
		else
			start_one_shot_state(g, SPECIAL);
		return ;
	}
	if (g->input.reload && state != RELOAD)
	{
		g->input.reload = 0;
		if (state == SPRINT)
			start_sprint_reverse(g, RELOAD);
		else
			start_one_shot_state(g, RELOAD);
		return ;
	}
	if (g->input.shoot && state == IDLE)
	{
		g->input.shoot = 0;
		start_one_shot_state(g, SHOOT);
		return ;
	}
	if (g->input.aim)
	{
		if (state == SPRINT)
		{
			start_sprint_reverse(g, AIM_IN);
			return ;
		}
		if (state != AIM && state != AIM_IN)
		{
			start_one_shot_state(g, AIM_IN);
			return ;
		}
		return ;
	}
	if (state == AIM && !g->input.aim)
	{
		start_one_shot_state(g, AIM_OUT);
		return ;
	}
	if (is_sprinting(g))
	{
		if (state != SPRINT)
			start_sprint_enter(g);
		return ;
	}
	if (state == SPRINT)
	{
		start_sprint_reverse(g, weapon_loop_state(g));
		return ;
	}
	advance_weapon_frame(g);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:42:10 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	weapon_handle_blocking(t_game *g)
{
	advance_weapon_frame(g);
	if (weapon_frame_finished(g))
		finish_blocking_state(g);
	return (1);
}

static int	weapon_handle_actions(t_game *g, int state)
{
	if (g->input.special && state != SPECIAL)
	{
		g->input.special = 0;
		if (state == SPRINT)
			start_sprint_reverse(g, SPECIAL);
		else
			start_one_shot_state(g, SPECIAL);
		return (1);
	}
	if (g->input.reload && state != RELOAD)
	{
		g->input.reload = 0;
		if (state == SPRINT)
			start_sprint_reverse(g, RELOAD);
		else
			start_one_shot_state(g, RELOAD);
		return (1);
	}
	if (g->input.shoot && state == IDLE)
	{
		g->input.shoot = 0;
		start_one_shot_state(g, SHOOT);
		return (1);
	}
	return (0);
}

static int	weapon_handle_aim(t_game *g, int state)
{
	if (g->input.aim)
	{
		if (state == SPRINT)
			start_sprint_reverse(g, AIM_IN);
		else if (state != AIM && state != AIM_IN)
			start_one_shot_state(g, AIM_IN);
		return (1);
	}
	if (state == AIM)
	{
		start_one_shot_state(g, AIM_OUT);
		return (1);
	}
	return (0);
}

static int	weapon_handle_sprint(t_game *g, int state)
{
	if (is_sprinting(g))
	{
		if (state != SPRINT)
			start_sprint_enter(g);
		return (1);
	}
	if (state == SPRINT)
	{
		start_sprint_reverse(g, weapon_loop_state(g));
		return (1);
	}
	return (0);
}

void	update_weapon(t_game *g)
{
	int	state;

	state = g->weapon.state;
	if (g->weapon.blocking)
	{
		weapon_handle_blocking(g);
		return ;
	}
	if (weapon_handle_actions(g, state))
		return ;
	if (weapon_handle_aim(g, state))
		return ;
	if (weapon_handle_sprint(g, state))
		return ;
	advance_weapon_frame(g);
}

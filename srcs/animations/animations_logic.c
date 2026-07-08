/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_logic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 15:31:31 by julepere          #+#    #+#             */
/*   Updated: 2026/07/05 22:06:12 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_weapon(t_game *g)
{
	int	state;

	state = g->weapon.state;
	
	if (g->input.special && state != SPECIAL)
	{
		g->input.special = 0;
		if (g->weapon.blocking)
		{
			g->weapon.next_state = SPECIAL;
		}
		set_state(g, SPECIAL, 0, 0);
		g->weapon.blocking = 1;
	}

	if (g->input.reload && state != RELOAD)
	{
		g->input.reload = 0;
		if (g->weapon.blocking)
		{
			g->weapon.next_state = RELOAD;
			return ;
		}
	}
	return (set_state(g, SPECIAL, 0, 0));

		
	if (g->input.reload && state != RELOAD)
		return (set_state(g, RELOAD, 0, 0));
	if (g->input.shoot && (state == IDLE || state == WALK))
		return (set_state(g, SHOOT, 0, 0));
	if (g->input.aim)
	{
		if (state == SPRINT)
			set_state(g, SPRINT, 0, 1);
		else if (state != AIM && state != AIM_IN)
			set_state(g, AIM_IN, 0, 0);
		return ;
	}
	if (state == AIM && !g->input.aim)
		return (set_state(g, AIM_OUT, 0, 0));
	if (is_sprinting(g) && state != SPRINT)
		return (set_state(g, SPRINT, 0, 0));
	if (!is_sprinting(g) && state == SPRINT && g->weapon.reversed == 0)
		return (set_state(g, SPRINT, 0, 1));
	if (is_moving(g) && state == IDLE)
		return (set_state(g, WALK, 1, 0));
	if (!is_moving(g) && state == WALK)
		return (set_state(g, IDLE, 1, 0));
}
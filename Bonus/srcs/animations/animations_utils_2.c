/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:07:12 by julepere          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_state(t_game *g, int state, int looping, int reversed)
{
	g->weapon.current = 0;
	g->weapon.tick = 0;
	g->weapon.state = state;
	g->weapon.looping = looping;
	g->weapon.reversed = reversed;
	g->weapon.hidden = 0;
}

int	is_moving(t_game *g)
{
	return (g->input.up || g->input.down
		|| g->input.left || g->input.right);
}

int	is_sprinting(t_game *g)
{
	return (g->input.shift && g->input.up);
}

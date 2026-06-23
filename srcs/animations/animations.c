/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:09:09 by julepere          #+#    #+#             */
/*   Updated: 2026/06/23 12:26:15 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

#define WEAPON_PATH "assets/weapon"

int	load_weapon_anims(t_game *g)
{
	if (load_anim(g, IDLE, WEAPON_PATH"/estatico", "estatico", 6))
		return (1);
	if (load_anim(g, WALK, WEAPON_PATH"/movimiento", "movimiento", 4))
		return (1);
	if (load_anim(g, SPRINT, WEAPON_PATH"/sprint", "sprint", 2))
		return (1);
	if (load_anim(g, RELOAD, WEAPON_PATH"/recarga", "recarga", 16))
		return (1);
	if (load_anim(g, AIM_IN, WEAPON_PATH"/apuntar", "apuntar", 4))
		return (1);
	if (load_anim(g, AIM_OUT, WEAPON_PATH"/desapuntar", "desapuntar", 4))
		return (1);
	if (load_anim(g, SHOOT, WEAPON_PATH"/disparo", "disparo", 3))
		return (1);
	if (load_anim(g, SPECIAL, WEAPON_PATH"/animacion", "animacion", 20))
		return (1);
	return (0);
}

static void	set_state(t_game *g, int state, int looping, int reversed)
{
	g->weapon.state = state;
	g->weapon.current = 0;
	g->weapon.tick = 0;
	g->weapon.looping = looping;
	g->weapon.reversed = reversed;
}

static int	is_moving(t_game *g)
{
	return (g->input.up || g->input.down
		|| g->input.left || g->input.right);
}

static int	is_sprinting(t_game *g)
{
	return (g->input.shift && g->input.up);
}

void	update_weapon_state(t_game *g)
{
	int	state;

	state = g->weapon.state;
	if (g->input.special && state != SPECIAL)
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

static void	advance_frame(t_game *g)
{
	int	last;

	last = g->weapon.frame_count[g->weapon.state] - 1;
	g->weapon.tick++;
	if (g->weapon.tick < g->weapon.speed)
		return ;
	g->weapon.tick = 0;
	if (g->weapon.reversed)
	{
		if (g->weapon.current > 0)
			g->weapon.current--;
		else if (g->weapon.looping)
			g->weapon.current = last;
		else
			update_weapon_state(g);
	}
	else
	{
		if (g->weapon.current < last)
			g->weapon.current++;
		else if (g->weapon.looping)
			g->weapon.current = 0;
		else
			update_weapon_state(g);
	}
}

void	update_weapon(t_game *g)
{
	update_weapon_state(g);
	advance_frame(g);
}

void	render_weapon(t_game *g)
{
	t_frame	frame;
	int		x;
	int		y;
	unsigned int	color;
	int		tex_x;
	int		tex_y;

	frame = g->weapon.frames[g->weapon.state][g->weapon.current];
	y = 0;
	while (y < g->config.height)
	{
		x = 0;
		while (x < g->config.width)
		{
			tex_x = x * frame.width / g->config.width;
			tex_y = y * frame.height / g->config.height;
			color = *(unsigned int *)(frame.addr
					+ (tex_y * frame.line_len + tex_x * (frame.bpp / 8)));
			if (color != 0xFF000000)
				pixel_put(&g->img, x, y, color);
			x++;
		}
		y++;
	}
}
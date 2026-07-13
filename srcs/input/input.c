/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:08:23 by julepere          #+#    #+#             */
/*   Updated: 2026/06/23 15:40:36 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	key_pause(t_game *g)
{
	if (g->state == STATE_GAME)
	{
		g->state = STATE_PAUSE;
		mlx_mouse_show(g->mlx, g->win);
	}
	else
	{
		g->state = STATE_GAME;
		mlx_mouse_hide(g->mlx, g->win);
	}
	return (0);
}

int	key_press(int keycode, t_game *g)
{
	if (keycode == 65307)
		return (close_window(g));
	if (keycode == 112)
		return (key_pause(g));
	if (keycode == 119)
		g->input.up = 1;
	if (keycode == 115)
		g->input.down = 1;
	if (keycode == 97)
		g->input.left = 1;
	if (keycode == 100)
		g->input.right = 1;
	if (keycode == 65361)
		g->input.arrow_left = 1;
	if (keycode == 65363)
		g->input.arrow_right = 1;
	if (keycode == 65505 || keycode == 65506)
		g->input.shift = 1;
	if (keycode == 114)
		g->input.reload = 1;
	if (keycode == 116)
		g->input.special = 1;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	if (g->state == STATE_PAUSE)
		return (0);
	if (keycode == 119)
		g->input.up = 0;
	if (keycode == 115)
		g->input.down = 0;
	if (keycode == 97)
		g->input.left = 0;
	if (keycode == 100)
		g->input.right = 0;
	if (keycode == 65361)
		g->input.arrow_left = 0;
	if (keycode == 65363)
		g->input.arrow_right = 0;
	if (keycode == 65505 || keycode == 65506)
		g->input.shift = 0;
	if (keycode == 114)
		g->input.reload = 0;
	if (keycode == 116)
		g->input.special = 0;
	return (0);
}

int	mouse_press(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (g->state == STATE_PAUSE)
		return (0);
	if (button == 1)
		g->input.shoot = 1;
	if (button == 3)
		g->input.aim = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (g->state == STATE_PAUSE)
		return (0);
	if (button == 1)
		g->input.shoot = 0;
	if (button == 3)
		g->input.aim = 0;
	return (0);
}

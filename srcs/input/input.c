/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:08:23 by julepere          #+#    #+#             */
/*   Updated: 2026/06/11 13:43:21 by jojeda-p         ###   ########.fr       */
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
	return (0);
}

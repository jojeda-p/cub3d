/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:08:23 by julepere          #+#    #+#             */
/*   Updated: 2026/06/01 16:47:39 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void key_press(int keycode, t_game *g)
{
	if (keycode == 65307)
		return (close_window(g));
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
}

void key_release(int keycode, t_game *g)
{
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
}
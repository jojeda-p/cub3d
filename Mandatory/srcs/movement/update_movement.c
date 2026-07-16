/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:16:48 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 13:05:08 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

void	update_player(t_game *g)
{
	int		forward;
	int		strafe;
	double	angle;

	angle = 0;
	forward = (g->input.up != 0) - (g->input.down != 0);
	strafe = (g->input.right != 0) - (g->input.left != 0);
	if (forward == 1)
		move_forward(g);
	else if (forward == -1)
		move_backward(g);
	if (strafe == 1)
		move_right(g);
	else if (strafe == -1)
		move_left(g);
	move_player(g);
	if (g->input.arrow_left && !g->input.arrow_right)
		angle -= g->player.rot_speed;
	else if (g->input.arrow_right && !g->input.arrow_left)
		angle += g->player.rot_speed;
	rotate_camera(angle, g);
}

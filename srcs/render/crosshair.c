/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 21:26:10 by julepere          #+#    #+#             */
/*   Updated: 2026/07/10 21:29:37 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_crosshair(t_game *g)
{
	int	center_x;
	int	center_y;
	int	offset;
	int	color;

	center_x = g->config.width / 2;
	center_y = g->config.height / 2;
	color = 0xFFFFFF;
	offset = -5;
	while (offset <= 5)
	{
		if (offset != 0)
		{
			pixel_put(&g->img, center_x + offset, center_y, color);
			pixel_put(&g->img, center_x, center_y + offset, color);
		}
		offset++;
	}
}
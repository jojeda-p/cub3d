/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:43:19 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/16 13:22:10 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_game *g, int y, int column)
{
	int	i;

	i = 0;
	while (i < y)
	{
		pixel_put(&g->img, column, i, g->config.ceiling_color);
		i++;
	}
	i = g->ray.draw_end;
	while (i < g->config.height)
	{
		pixel_put(&g->img, column, i, g->config.floor_color);
		i++;
	}
}

int	get_tex_y(t_tex texture, double tex_pos)
{
	int	tex_y;

	tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture.height)
			tex_y = texture.height - 1;
	return (tex_y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:16:56 by josu              #+#    #+#             */
/*   Updated: 2026/07/05 19:20:26 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static int	get_tex_color_no_fog(t_tex texture, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	color;
	unsigned char	*pixel;
	int				i;

	if (tex_x < 0 || tex_x >= texture.width || tex_y < 0
		|| tex_y >= texture.height)
		return (0);
	offset = tex_y * texture.line_len + tex_x * (texture.bpp / 8);
	pixel = (unsigned char *)texture.addr + offset;
	if ((texture.bpp / 8) == 4)
		color = *(unsigned int *)pixel;
	else
	{
		color = 0;
		i = 0;
		while (i < (texture.bpp / 8))
		{
			color |= ((unsigned int)pixel[i]) << (8 * i);
			i++;
		}
	}
	return ((int)color);
}

int	render_pause(t_game *g)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = 0;
	while (y < g->config.height)
	{
		x = 0;
		while (x < g->config.width)
		{
			tex_x = x * g->pause_tex.width / g->config.width;
			tex_y = y * g->pause_tex.height / g->config.height;
			color = get_tex_color_no_fog(g->pause_tex, tex_x, tex_y);
			pixel_put(&g->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}

int	render_end(t_game *g)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = 0;
	while (y < g->config.height)
	{
		x = 0;
		while (x < g->config.width)
		{
			tex_x = x * g->end.width / g->config.width;
			tex_y = y * g->end.height / g->config.height;
			color = get_tex_color_no_fog(g->end, tex_x, tex_y);
			pixel_put(&g->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}
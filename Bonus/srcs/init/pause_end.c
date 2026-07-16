/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:16:56 by josu              #+#    #+#             */
/*   Updated: 2026/07/15 14:57:54 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include "mlx.h"

static int	load_pause_tex(t_game *g)
{
	g->pause_tex.img = mlx_xpm_file_to_image(g->mlx, g->pause_tex.path,
			&g->pause_tex.width, &g->pause_tex.height);
	if (!g->pause_tex.img)
		return (1);
	g->pause_tex.addr = mlx_get_data_addr(g->pause_tex.img, &g->pause_tex.bpp,
			&g->pause_tex.line_len, &g->pause_tex.endian);
	if (!g->pause_tex.addr)
	{
		mlx_destroy_image(g->mlx, g->pause_tex.img);
		g->pause_tex.img = NULL;
		return (1);
	}
	return (0);
}

int	load_end_pause_texture(t_game *g)
{
	if (load_pause_tex(g))
		return (1);
	g->end.img = mlx_xpm_file_to_image(g->mlx, g->end.path,
			&g->end.width, &g->end.height);
	if (!g->end.img)
	{
		mlx_destroy_image(g->mlx, g->pause_tex.img);
		g->pause_tex.img = NULL;
		return (1);
	}
	g->end.addr = mlx_get_data_addr(g->end.img, &g->end.bpp,
			&g->end.line_len, &g->end.endian);
	if (!g->end.addr)
	{
		mlx_destroy_image(g->mlx, g->end.img);
		g->end.img = NULL;
		mlx_destroy_image(g->mlx, g->pause_tex.img);
		g->pause_tex.img = NULL;
		return (1);
	}
	return (0);
}

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

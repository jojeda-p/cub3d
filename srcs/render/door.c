/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:46:44 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/22 18:52:05 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	load_door(t_game *g)
{
	int	i;

	if (g->config.door == 0)
		return ;
	i = 0;
	while (i < g->config.door)
	{
		g->door[i].tex.path = "assets/puerta.xpm";
		i++;
	}
}

int	load_door_texture(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->config.door)
	{
		g->door[i].tex.img = mlx_xpm_file_to_image(g->mlx, 
			g->door[i].tex.path, &g->door[i].tex.width,
			&g->door[i].tex.height);
		if (!g->door[i].tex.img)
			return (1);
		g->door[i].tex.addr =  mlx_get_data_addr(g->door[i].tex.img,
			&g->door[i].tex.bpp, &g->door[i].tex.line_len,
			&g->door[i].tex.endian);
		if (!g->door[i].tex.addr)
			return (1);
		i++;
	}
	return (0);
}

void	update_door(t_game *g, int i)
{
	double	proximity;
	double	dist;
	double	dx;
	double	dy;
	double	door_speed;

	dx = g->door[i].x - g->player.x;
	dy = g->door[i].y - g->player.y;
	dist = sqrt(dx * dx + dy * dy);
	proximity = 1.5 * g->map.tile_size;
	door_speed = 0.05;
	if (dist < proximity)
	{
		if (g->door[i].open_progress < 1.0)
			g->door[i].open_progress = g->door[i].open_progress + door_speed;
	}
	else
	{
		if (g->door[i].open_progress > 0.0)
			g->door[i].open_progress = g->door[i].open_progress - door_speed;
	}
}

void	calculate_door_2(t_game *g, int i)
{
	g->door[i].draw_start_y = -g->door[i].height / 2 + g->config.height / 2;
	g->door[i].draw_end_y = g->door[i].height / 2 + g->config.height / 2;
	if (g->door[i].draw_start_y < 0)
		g->door[i].draw_start_y = 0;
	if (g->door[i].draw_end_y >= g->config.height)
		g->door[i].draw_end_y = g->config.height - 1;
	g->door[i].draw_start_x = -g->door[i].width / 2 + g->door[i].screen_x;
	g->door[i].draw_end_x = g->door[i].width / 2 + g->door[i].screen_x;
	if (g->door[i].draw_start_x < 0)
		g->door[i].draw_start_x = 0;
	if (g->door[i].draw_end_x >= g->config.width)
		g->door[i].draw_end_x = g->config.width - 1;
}

int	calculate_door(t_game *g, int i)
{
	double	p[4];
	double	t[4];
	double	inv;
	int		scr[2];

	p[0] = (g->door[i].x - g->player.x) / g->map.tile_size;
	p[1] = (g->door[i].y - g->player.y) / g->map.tile_size;
	if (g->door[i].dir == 0)
	{
		p[2] = p[0] + 0.5;
		p[0] = p[0] - 0.5;
		p[3] = p[1];
	}
	else
	{
		p[2] = p[0];
		p[3] = p[1] + 0.5;
		p[1] = p[1] - 0.5;
	}
	inv = 1.0 / (g->camera.plane_x * g->player.dir_y
			- g->player.dir_x * g->camera.plane_y);
	t[0] = inv * (g->player.dir_y * p[0] - g->player.dir_x * p[1]);
	t[1] = inv * (-g->camera.plane_y * p[0] + g->camera.plane_x * p[1]);
	t[2] = inv * (g->player.dir_y * p[2] - g->player.dir_x * p[3]);
	t[3] = inv * (-g->camera.plane_y * p[2] + g->camera.plane_x * p[3]);
	if (t[1] <= 0.1 && t[3] <= 0.1)
		return (0);
	scr[0] = (int)((g->config.width / 2.0) * (1.0 + t[0] / t[1]));
	scr[1] = (int)((g->config.width / 2.0) * (1.0 + t[2] / t[3]));
	g->door[i].width = abs(scr[1] - scr[0]);
	if (g->door[i].width <= 0)
		return (0);
	g->door[i].screen_x = (scr[0] + scr[1]) / 2;
	g->door[i].transform_y = (t[1] + t[3]) / 2.0;
	g->door[i].height = abs((int)(g->config.height / g->door[i].transform_y));
	calculate_door_2(g, i);
	return (1);
}

void	get_door_tex_x(t_game *g, int x, int i)
{
    int     d;
    int     tex_offset;
    t_tex   tex;

    tex = g->door[i].tex;
    tex_offset = (int)(tex.width * g->door[i].open_progress);
    d = x - (g->door[i].screen_x - g->door[i].width / 2);
    g->door[i].tex_x = tex_offset + d * tex.width / g->door[i].width;
    if (g->door[i].tex_x < 0)
        g->door[i].tex_x = 0;
    if (g->door[i].tex_x >= tex.width)
        g->door[i].tex_x = tex.width - 1;
}

void	get_door_tex_y(t_game *g, int y, int i)
{
	int	d;

	d = y - g->door[i].draw_start_y;
	g->door[i].tex_y = d * g->door[i].tex.height / g->door[i].height;
	if (g->door[i].tex_y < 0)
		g->door[i].tex_y = 0;
	if (g->door[i].tex_y >= g->door[i].tex.height)
		g->door[i].tex_y = g->door[i].tex.height - 1;
}

int	get_door_color(t_game *g, int i, int tex_x, int tex_y)
{
	int				offset;
	unsigned int	color;
	unsigned char	*pixel;
	int				j;

	if (tex_x < 0 || tex_x >= g->door[i].tex.width || tex_y < 0
		|| tex_y >= g->door[i].tex.height)
		return (0);
	offset = tex_y * g->door[i].tex.line_len 
		+ tex_x * (g->door[i].tex.bpp / 8);
	pixel = (unsigned char *)g->door[i].tex.addr + offset;
	if ((g->door[i].tex.bpp / 8) == 4)
		color = *(unsigned int *)pixel;
	else
	{
		color = 0;
		j = 0;
		while (j < (g->door[i].tex.bpp / 8))
		{
			color |= ((unsigned int)pixel[j]) << (8 * j);
			j++;
		}
	}
	color = ft_fog(g, color);
	return ((int)color);
}

void	draw_door(t_game *g, int i)
{
	int	x;
	int	y;
	int	color;
	int	real_end;

	real_end = g->door[i].draw_start_x
		+ (int)(g->door[i].width * (1.0 - g->door[i].open_progress));
	if (real_end > g->door[i].draw_end_x)
		real_end = g->door[i].draw_end_x;
	x = g->door[i].draw_start_x;
	while (x < real_end)
	{
		if (g->door[i].transform_y < g->ray.z_buf[x])
		{
			get_door_tex_x(g, x, i);
			y = g->door[i].draw_start_y;
			while (y < g->door[i].draw_end_y)
			{
				get_door_tex_y(g, y, i);
				color = get_door_color(g, i, g->door[i].tex_x,
					g->door[i].tex_y);
				pixel_put(&g->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void    render_doors(t_game *g)
{
    int i;

    i = 0;
    while (i < g->config.door)
    {
        update_door(g, i);
        if (g->door[i].open_progress < 1.0)
        {
            if (calculate_door(g, i))
                draw_door(g, i);
        }
        i++;
    }
}

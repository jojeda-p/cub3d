/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:46:44 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/23 17:17:05 by jojeda-p         ###   ########.fr       */
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

int	find_door(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->config.door)
	{
		if (g->door[i].map_x / g->map.tile_size == x
            && g->door[i].map_y / g->map.tile_size == y)
			return (i);
		i++;
	}
	return (-1);
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

void draw_door_column(t_game *g, int column, int i)
{
    int     y;
    int     color;

    if (!isfinite(g->door[i].perp_dist) || g->door[i].perp_dist <= 0.0)
        return ;
    g->door[i].line_height = g->ray.line_height;
    g->door[i].draw_start = -g->door[i].line_height / 2 + g->config.height / 2;
    if (g->door[i].draw_start < 0)
        g->door[i].draw_start = 0;
    g->door[i].draw_end = g->door[i].line_height / 2 + g->config.height / 2;
    if (g->door[i].draw_end >= g->config.height)
        g->door[i].draw_end = g->config.height - 1;
    if (g->door[i].line_height <= 0 || g->door[i].tex.height <= 0)
        return ;
    g->door[i].step = (double)g->door[i].tex.height / g->door[i].line_height;
    g->door[i].tex_pos = (g->door[i].draw_start - g->config.height / 2
        + g->door[i].line_height / 2) * g->door[i].step;
    y = g->door[i].draw_start;
    while (y <= g->door[i].draw_end)
    {
        g->door[i].tex_y = (int)g->door[i].tex_pos;
        if (g->door[i].tex_y < 0)
            g->door[i].tex_y = 0;
        if (g->door[i].tex_y >= g->door[i].tex.height)
            g->door[i].tex_y = g->door[i].tex.height - 1;
        g->door[i].tex_pos += g->door[i].step;
        color = get_door_color(g, i, g->door[i].tex_x, g->door[i].tex_y);
        if (color != 0)
            pixel_put(&g->img, column, y, color);
        y++;
    }
    g->ray.z_buf[column] = g->door[i].perp_dist;
}

double  get_door_perp_dist(t_game *g, int i)
{
    double  perp_dist;
    double  exact_hit;
    int     tex_x;
    int     tex_offset;
    double  pos_x;
    double  pos_y;

    pos_x = g->player.x / g->map.tile_size;
    pos_y = g->player.y / g->map.tile_size;
    
    if (g->door[i].dir == 0) // Puerta horizontal (separando Norte/Sur)
    {
        perp_dist = g->ray.side_dist_y - (g->ray.delta_dist_y / 2.0);
        exact_hit = pos_x + perp_dist * g->ray.ray_dir_x;
        if (exact_hit < (double)g->ray.map_x || exact_hit > (double)(g->ray.map_x + 1))
            return (-1.0);
        exact_hit = exact_hit - floor(exact_hit);
        if (g->ray.ray_dir_y > 0)
            exact_hit = 1.0 - exact_hit;
    }
    else // Puerta vertical (separando Este/Oeste)
    {
        perp_dist = g->ray.side_dist_x - (g->ray.delta_dist_x / 2.0);
        exact_hit = pos_y + perp_dist * g->ray.ray_dir_y;
        if (exact_hit < (double)g->ray.map_y || exact_hit > (double)(g->ray.map_y + 1))
            return (-1.0);
        exact_hit = exact_hit - floor(exact_hit);
        if (g->ray.ray_dir_x < 0)
            exact_hit = 1.0 - exact_hit;
    }
    if (perp_dist <= 0)
        return (-1.0);
    tex_offset = (int)(g->door[i].tex.width * g->door[i].open_progress);
    tex_x = tex_offset + (int)(exact_hit * g->door[i].tex.width);
    if (tex_x >= g->door[i].tex.width || tex_x < 0)
        return (-1.0);
    g->door[i].tex_x = tex_x;
    return (perp_dist);
}

void	door_render(t_game *g)
{
	int		i;
	double	perp_dist;

	i = find_door(g, g->ray.map_x, g->ray.map_y);
	if (i >= 0)
	{
		perp_dist = get_door_perp_dist(g, i);
		if (perp_dist > 0)
		{
			g->ray.door_hit = i;
			g->ray.door_perp = perp_dist;
			g->ray.hit = 1;
		}
	}
}

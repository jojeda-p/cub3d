/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:31:27 by josu              #+#    #+#             */
/*   Updated: 2026/06/19 14:09:49 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>

void    load_sprite_textures(t_game *g)
{
    int i;
    int j;

    i = 0;
    while (i < g->config.sprite)
    {
        j = 0;
        while (j < g->sprite[i].num_frames)
        {
            g->sprite[i].frames[j].img = mlx_xpm_file_to_image(g->mlx,
                g->sprite[i].frames[j].path, &g->sprite[i].frames[j].width,
                &g->sprite[i].frames[j].height);
            if (!g->sprite[i].frames[j].img)
                return ;
            g->sprite[i].frames[j].addr = mlx_get_data_addr(
                g->sprite[i].frames[j].img, &g->sprite[i].frames[j].bpp,
                &g->sprite[i].frames[j].line_len,
                &g->sprite[i].frames[j].endian);
            if (!g->sprite[i].frames[j].addr)
                return ;
            g->sprite[i].collected = 0;
            j++;
        }
        i++;
    }
}
void	load_sprite(t_game *g)
{
	if (g->config.sprite == 0)
		return ;
	g->sprite->frames[0].path = "assets/gifs/ammo/frame-01_d91799e7fc3f0624.xpm";
	g->sprite->frames[1].path = "assets/gifs/ammo/frame-02_4a933ead264cfa2b.xpm";
	g->sprite->frames[2].path = "assets/gifs/ammo/frame-03_b79cdb7ee28aae12.xpm";
	g->sprite->frames[3].path = "assets/gifs/ammo/frame-04_afbc3aac2adad0ff.xpm";
	g->sprite->frames[4].path = "assets/gifs/ammo/frame-05_4cb3db0d5445dc8f.xpm";
	g->sprite->frames[5].path = "assets/gifs/ammo/frame-06_38e6064d71e04f66.xpm";
	g->sprite->frames[6].path = "assets/gifs/ammo/frame-07_85f49baae2526ccd.xpm";
	g->sprite->frames[7].path = "assets/gifs/ammo/frame-08_5aa33e977451265d.xpm";
	g->sprite->frames[8].path = "assets/gifs/ammo/frame-09_9d4c2f98a419c85d.xpm";
	g->sprite->frames[9].path = "assets/gifs/ammo/frame-10_9138fdcf831b3250.xpm";
	g->sprite->frames[10].path = "assets/gifs/ammo/frame-11_b4f1814279110c43.xpm";
	g->sprite->frames[11].path = "assets/gifs/ammo/frame-12_0f6ef9977c6932c0.xpm";
	g->sprite->frames[12].path = "assets/gifs/ammo/frame-13_a06e1990d54f12b7.xpm";
	g->sprite->frames[13].path = "assets/gifs/ammo/frame-14_981f80ae2a0793c0.xpm";
	g->sprite->frames[14].path = "assets/gifs/ammo/frame-15_0bd2e9311c7fde58.xpm";
	g->sprite->frames[15].path = "assets/gifs/ammo/frame-16_b9bb01280874aead.xpm";
	g->sprite[0].num_frames = 16;
    g->sprite[0].current_frame = 0;
}
int get_sprite_tex_x(t_game *g, int x, int i)
{
    int tex_x;
    int d;

    d = x - (g->sprite[i].screen_x - g->sprite[i].width / 2);
    tex_x = d * g->sprite[i].frames[g->sprite[i].current_frame].width
    / g->sprite[i].width;
    return (tex_x);
}

int get_sprite_tex_y(t_game *g, int y, int i)
{
    int tex_y;
    int d;

    d = y - g->sprite[i].draw_start_y;
    tex_y = d * g->sprite[i].frames[g->sprite[i].current_frame].height
    / g->sprite[i].height;
    return (tex_y);
}

int get_sprite_color(t_game *g, int i, int tex_x, int tex_y)
{
    int				offset;
	unsigned int	color;
	unsigned char	*pixel;
	int				j;

	if (tex_x < 0 || tex_x >= g->sprite[i].frames[g->sprite[i].current_frame].width
    || tex_y < 0 || tex_y >= g->sprite[i].frames[g->sprite[i].current_frame].height)
        return (0);
	offset = tex_y * g->sprite[i].frames[g->sprite[i].current_frame].line_len
    + tex_x * (g->sprite[i].frames[g->sprite[i].current_frame].bpp / 8);
	pixel = (unsigned char *)
    g->sprite[i].frames[g->sprite[i].current_frame].addr + offset;
	if ((g->sprite[i].frames[g->sprite[i].current_frame].bpp / 8) == 4)
		color = *(unsigned int *)pixel;
	else
	{
		color = 0;
		j = 0;
		while (j < (g->sprite[i].frames[g->sprite[i].current_frame].bpp / 8))
		{
			color |= ((unsigned int)pixel[j]) << (8 * j);
			j++;
		}
	}
	/* color = ft_fog(g, color); */
	return ((int)color);
}


void    update_sprite_animation(t_game *g)
{
    int i;

    g->config.anim_speed = 10;
    g->config.frame_counter++;
    if (g->config.frame_counter < g->config.anim_speed)
        return ;
    g->config.frame_counter = 0;
    i = 0;
    while (i < g->config.sprite)
    {
        g->sprite[i].current_frame = (g->sprite[i].current_frame + 1)
            % g->sprite[i].num_frames;
        i++;
    }
}

void    check_sprite_pickup(t_game *g)//falta que quite delmapa el sprite
{
    int     i;
    double  dist;
    double  pickup_rad;

    pickup_rad = 50;
    i = 0;
    while (i < g->config.sprite)
    {
        if (!g->sprite[i].collected)
        {
            dist = sqrt(g->sprite[i].distance);
            if (dist < pickup_rad)
                g->sprite[i].collected = 1;
        }
        i++;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:43:19 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/16 16:44:55 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

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
            j++;
        }
        i++;
    }
}

void	load_sprite(t_game *g)
{
	if (g->config.sprite == 0)
		return ;
	g->sprite->frames[0].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-01_d91799e7fc3f0624.xpm";
	g->sprite->frames[1].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-02_4a933ead264cfa2b.xpm";
	g->sprite->frames[2].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-03_b79cdb7ee28aae12.xpm";
	g->sprite->frames[3].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-04_afbc3aac2adad0ff.xpm";
	g->sprite->frames[4].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-05_4cb3db0d5445dc8f.xpm";
	g->sprite->frames[5].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-06_38e6064d71e04f66.xpm";
	g->sprite->frames[6].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-07_85f49baae2526ccd.xpm";
	g->sprite->frames[7].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-08_5aa33e977451265d.xpm";
	g->sprite->frames[8].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-09_9d4c2f98a419c85d.xpm";
	g->sprite->frames[9].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-10_9138fdcf831b3250.xpm";
	g->sprite->frames[10].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-11_b4f1814279110c43.xpm";
	g->sprite->frames[11].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-12_0f6ef9977c6932c0.xpm";
	g->sprite->frames[12].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-13_a06e1990d54f12b7.xpm";
	g->sprite->frames[13].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-14_981f80ae2a0793c0.xpm";
	g->sprite->frames[14].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-15_0bd2e9311c7fde58.xpm";
	g->sprite->frames[15].path = "/sgoinfre/students/jojeda-p/42cursus/M4/cub3d/assets/gifs/ammo/frame-16_b9bb01280874aead.xpm";
	g->sprite[0].num_frames = 16;
    g->sprite[0].current_frame = 0;
}

void	order_sprites(t_game *g)
{
	int			i;
	double		dx;
	double		dy;
	t_sprite	aux;

	i = 0;
	while (i < g->config.sprite - 1)
	{
		dx = g->sprite[i].x - g->player.x;
		dy = g->sprite[i].y - g->player.y;
		g->sprite[i].distance = dx * dx + dy * dy;
		i++;
	}
	i = 0;
	while (i < g->config.sprite)
	{
		if (g->sprite[i].distance < g->sprite[i + 1].distance)
		{
			aux = g->sprite[i];
			g->sprite[i] = g->sprite[i + 1];
			g->sprite[i + 1] = aux;
			i = -1;
		}
		i++;
	}
}

/* void	calculate_sprite(t_game *g, int i)
{
	
}

void	draw_sprite(t_game *g, int i)
{
	
} */

void	render_sprites(t_game *g)
{
	int	i;

	order_sprites(g);
	i = 0;
	while (i < g->config.sprite)
	{
		/* calculate_sprite(g, i);
		draw_sprite(g, i); */
		i++;
	}
}

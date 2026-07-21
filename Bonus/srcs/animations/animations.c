/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:09:09 by julepere          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include "stdlib.h"

#define WEAPON_PATH "assets/weapon"

static void	free_static_frame(t_game *g, int state, t_frame *frame)
{
	if (frame->img)
		mlx_destroy_image(g->mlx, frame->img);
	free(g->weapon.frames[state]);
	g->weapon.frames[state] = NULL;
	g->weapon.frame_count[state] = 0;
}

static int	load_static_frame(t_game *g, int state, char *path)
{
	t_frame	*frame;

	g->weapon.frames[state] = malloc(sizeof(t_frame));
	if (!g->weapon.frames[state])
		return (1);
	g->weapon.frames[state][0] = (t_frame){0};
	g->weapon.frame_count[state] = 1;
	frame = &g->weapon.frames[state][0];
	frame->img = mlx_xpm_file_to_image(g->mlx, path,
			&frame->width, &frame->height);
	if (!frame->img)
		return (free_static_frame(g, state, frame), 1);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp,
			&frame->line_len, &frame->endian);
	if (!frame->addr)
		return (free_static_frame(g, state, frame), 1);
	return (0);
}

int	load_weapon_anims(t_game *g)
{
	if (load_anim(g, IDLE, WEAPON_PATH"/estatico", 6))
		return (1);
	if (load_anim(g, SPRINT, WEAPON_PATH"/sprint", 2))
		return (1);
	if (load_anim(g, RELOAD, WEAPON_PATH"/recarga", 16))
		return (1);
	if (load_static_frame(g, AIM, WEAPON_PATH"/apuntado_estatico.xpm"))
		return (1);
	if (load_anim(g, AIM_IN, WEAPON_PATH"/apuntar", 4))
		return (1);
	if (load_anim(g, AIM_OUT, WEAPON_PATH"/desapuntar", 4))
		return (1);
	if (load_anim(g, SHOOT, WEAPON_PATH"/disparo", 3))
		return (1);
	if (load_anim(g, SPECIAL, WEAPON_PATH"/animacion", 20))
		return (1);
	return (0);
}

void	render_weapon(t_game *g)
{
	t_frame			frame;
	unsigned int	color;

	if (g->weapon.hidden)
		return ;
	frame = g->weapon.frames[g->weapon.state][g->weapon.current];
	g->weapon.y = 0;
	while (g->weapon.y < g->config.height)
	{
		g->weapon.x = 0;
		while (g->weapon.x < g->config.width)
		{
			g->weapon.tex_x = g->weapon.x * frame.width / g->config.width;
			g->weapon.tex_y = g->weapon.y * frame.height / g->config.height;
			color = *(unsigned int *)(frame.addr
					+ (g->weapon.tex_y * frame.line_len + g->weapon.tex_x
						* (frame.bpp / 8)));
			if (color != 0xFF000000)
				pixel_put(&g->img, g->weapon.x, g->weapon.y, color);
			g->weapon.x++;
		}
		g->weapon.y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:09:09 by julepere          #+#    #+#             */
/*   Updated: 2026/07/13 15:18:04 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "stdlib.h"

#define WEAPON_PATH "assets/weapon"

static int	load_static_frame(t_game *g, int state, char *path)
{
	t_frame	*frame;

	g->weapon.frames[state] = malloc(sizeof(t_frame));
	if (!g->weapon.frames[state])
		return (1);
	g->weapon.frame_count[state] = 1;
	frame = &g->weapon.frames[state][0];
	frame->img = mlx_xpm_file_to_image(g->mlx, path,
			&frame->width, &frame->height);
	if (!frame->img)
		return (1);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp,
			&frame->line_len, &frame->endian);
	if (!frame->addr)
		return (1);
	return (0);
}

int	load_weapon_anims(t_game *g)
{
	if (load_anim(g, IDLE, WEAPON_PATH"/estatico", "estatico", 6))
		return (1);
	if (load_anim(g, SPRINT, WEAPON_PATH"/sprint", "sprint", 2))
		return (1);
	if (load_anim(g, RELOAD, WEAPON_PATH"/recarga", "recarga", 16))
		return (1);
	if (load_static_frame(g, AIM, WEAPON_PATH"/apuntado_estatico.xpm"))
		return (1);
	if (load_anim(g, AIM_IN, WEAPON_PATH"/apuntar", "apuntar", 4))
		return (1);
	if (load_anim(g, AIM_OUT, WEAPON_PATH"/desapuntar", "desapuntar", 4))
		return (1);
	if (load_anim(g, SHOOT, WEAPON_PATH"/disparo", "disparo", 3))
		return (1);
	if (load_anim(g, SPECIAL, WEAPON_PATH"/animacion", "animacion", 20))
		return (1);
	return (0);
}

void	render_weapon(t_game *g)
{
	t_frame	frame;
	int		x;
	int		y;
	unsigned int	color;
	int		tex_x;
	int		tex_y;

	if (g->weapon.hidden)
		return ;

	frame = g->weapon.frames[g->weapon.state][g->weapon.current];
	y = 0;
	while (y < g->config.height)
	{
		x = 0;
		while (x < g->config.width)
		{
			tex_x = x * frame.width / g->config.width;
			tex_y = y * frame.height / g->config.height;
			color = *(unsigned int *)(frame.addr
					+ (tex_y * frame.line_len + tex_x * (frame.bpp / 8)));
			if (color != 0xFF000000)
				pixel_put(&g->img, x, y, color);
			x++;
		}
		y++;
	}
}

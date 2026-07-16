/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:30:48 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 13:11:15 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "mlx.h"

int	load_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		g->tex[i].img = mlx_xpm_file_to_image(g->mlx, g->tex[i].path,
				&g->tex[i].width, &g->tex[i].height);
		if (!g->tex[i].img)
			return (1);
		g->tex[i].addr = mlx_get_data_addr(g->tex[i].img, &g->tex[i].bpp,
				&g->tex[i].line_len, &g->tex[i].endian);
		if (!g->tex[i].addr)
			return (1);
		i++;
	}
	return (0);
}

t_tex	get_wall_texture(t_game *g)
{
	if (g->ray.side == 0)
	{
		if (g->ray.step_x == 1)
			return (g->tex[3]);
		return (g->tex[2]);
	}
	if (g->ray.step_y == 1)
		return (g->tex[0]);
	return (g->tex[1]);
}

int	ft_fog(t_game *g, int color)
{
	double	factor;
	int		r;
	int		b;
	int		gr;

	factor = 1.0 - (g->ray.perp_dist / 10.0);
	if (factor < 0.0)
		factor = 0.0;
	r = ((color >> 16) & 0xFF) * factor;
	gr = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (gr << 8) | b);
}

/*calculando la direccion del pixel movemos los bits de los 4 bytes
 que lo componen y los extraemos*/
int	get_tex_color(t_game *g, t_tex texture, int tex_x, int tex_y)
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
	color = ft_fog(g, color);
	return ((int)color);
}

/*Calcula la coordenada horizontal de la textura (columna) correspondiente
 al impacto de la pared por el rayo actual. Devuelve un entero en el
 rango [0 .. texture.width-1]. Gestiona el volteo y recorta el resultado
 para evitar accesos fuera de rango por redondeos de punto flotante.
 */
int	get_tex_x(t_game *g, t_tex texture)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0;
	if (g->ray.side == 0)
		wall_x = g->player.y / g->map.tile_size + g->ray.perp_dist
			* g->ray.ray_dir_y;
	else
		wall_x = g->player.x / g->map.tile_size + g->ray.perp_dist
			* g->ray.ray_dir_x;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * (double)texture.width);
	if (!((g->ray.side == 0 && g->ray.ray_dir_x > 0)
			|| (g->ray.side == 1 && g->ray.ray_dir_y < 0)))
		tex_x = texture.width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture.width)
		tex_x = texture.width - 1;
	return (tex_x);
}

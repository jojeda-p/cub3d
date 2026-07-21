/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:30:50 by josu              #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>

static int	valid_sprite_pixel(t_tex *tex, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_y < 0)
		return (0);
	if (tex_x >= tex->width || tex_y >= tex->height)
		return (0);
	return (1);
}

static unsigned int	get_raw_color(t_tex *tex, int tex_x, int tex_y)
{
	int				offset;
	int				bytes;
	int				j;
	unsigned int	color;
	unsigned char	*pixel;

	bytes = tex->bpp / 8;
	offset = tex_y * tex->line_len + tex_x * bytes;
	pixel = (unsigned char *)tex->addr + offset;
	if (bytes == 4)
		return (*(unsigned int *)pixel);
	color = 0;
	j = 0;
	while (j < bytes)
	{
		color |= ((unsigned int)pixel[j]) << (8 * j);
		j++;
	}
	return (color);
}

int	get_sprite_color(t_game *g, int i, int tex_x, int tex_y)
{
	t_tex			*tex;
	unsigned int	color;

	tex = &g->sprite[i].frames[g->sprite[i].current_frame];
	if (!valid_sprite_pixel(tex, tex_x, tex_y))
		return (0);
	color = get_raw_color(tex, tex_x, tex_y);
	if (color != 0xae17cc)
		color = ft_fog(color, g->sprite[i].transform_y);
	return ((int)color);
}

static int	ft_nbr_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa2(int n)
{
	char	*str;
	long	nb;
	int		len;

	nb = n;
	len = ft_nbr_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

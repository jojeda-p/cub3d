/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:18:53 by julepere          #+#    #+#             */
/*   Updated: 2026/06/23 12:22:01 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"

static char	*ft_itoa(int n)
{
	char	buf[12];
	int		i;

	i = 11;
	buf[i] = '\0';
	if (n == 0)
		buf[--i] = '0';
	while (n > 0)
	{
		buf[--i] = '0' + (n % 10);
		n /= 10;
	}
	return (ft_strdup(&buf[i]));
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*build_path(char *base, char *name, int n)
{
	char	*num;
	char	*tmp1;
	char	*tmp2;
	char	*result;

	num = ft_itoa(n);
	tmp1 = ft_strjoin(base, name);
	tmp2 = ft_strjoin(tmp1, "_");
	result = ft_strjoin(tmp2, num);
	free(tmp1);
	free(tmp2);
	free(num);
	tmp1 = ft_strjoin(result, ".xpm");
	free(result);
	return (tmp1);
}

static int	load_frame(t_game *g, t_frame *frame, char *path)
{
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

int	load_anim(t_game *g, int state, char *folder, char *name, int count)
{
	int		i;
	char	*base;
	char	*path;

	g->weapon.frames[state] = malloc(sizeof(t_frame) * count);
	if (!g->weapon.frames[state])
		return (1);
	g->weapon.frame_count[state] = count;
	base = ft_strjoin(folder, "/");
	i = 0;
	while (i < count)
	{
		path = build_path(base, name, i + 1);
		if (load_frame(g, &g->weapon.frames[state][i], path))
		{
			free(path);
			free(base);
			return (1);
		}
		free(path);
		i++;
	}
	free(base);
	return (0);
}
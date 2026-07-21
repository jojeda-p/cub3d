/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 22:18:53 by julepere          #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"

static char	*build_path(char *base, char *name, int n)
{
	char	*num;
	char	*result;

	num = ft_itoa(n);
	if (!num)
		return (NULL);
	result = ft_strjoin(base, name);
	result = join_free(result, "_");
	result = join_free(result, num);
	free(num);
	if (!result)
		return (NULL);
	return (join_free(result, ".xpm"));
}

int	load_frame(t_game *g, t_frame *frame, char *path)
{
	frame->img = mlx_xpm_file_to_image(g->mlx, path,
			&frame->width, &frame->height);
	if (!frame->img)
		return (1);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp,
			&frame->line_len, &frame->endian);
	if (!frame->addr)
	{
		mlx_destroy_image(g->mlx, frame->img);
		frame->img = NULL;
		return (1);
	}
	return (0);
}

char	*get_name(char *folder)
{
	char	*slash;

	slash = ft_strrchr(folder, '/');
	if (slash)
		return (slash + 1);
	return (folder);
}

static void	free_frames_on_fail(t_game *g, int state, int i)
{
	while (i > 0)
	{
		i--;
		if (g->weapon.frames[state][i].img)
			mlx_destroy_image(g->mlx, g->weapon.frames[state][i].img);
		g->weapon.frames[state][i].img = NULL;
	}
	free(g->weapon.frames[state]);
	g->weapon.frames[state] = NULL;
	g->weapon.frame_count[state] = 0;
}

int	load_frames_loop(t_game *g, int state, char *base, char *name)
{
	int		i;
	char	*path;

	i = 0;
	while (i < g->weapon.frame_count[state])
	{
		path = build_path(base, name, i + 1);
	if (!path)
	{
		free_frames_on_fail(g, state, i);
		return (1);
	}
		if (load_frame(g, &g->weapon.frames[state][i], path))
		{
			free(path);
			free_frames_on_fail(g, state, i);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

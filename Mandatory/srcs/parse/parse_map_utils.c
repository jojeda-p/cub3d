/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:42:48 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 12:36:26 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

int	valid_char(char c)
{
	if (c != ' ' && c != '0' && c != 'E' && c != 'S'
		&& c != '1' && c != 'N' && c != 'W' && c != '\n')
		return (0);
	return (1);
}

void	malloc_grid(char **matrix, t_game *g)
{
	int		i;
	int		j;
	int		k;

	i = 6;
	k = 0;
	while (matrix[i])
	{
		i++;
		k++;
	}
	g->map.grid = malloc(sizeof(char *) * (k + 1));
	i = 6;
	k = 0;
	while (matrix[i])
	{
		j = ft_strlen(matrix[i]) + 1;
		g->map.grid[k] = malloc(sizeof(char) * j);
		i++;
		k++;
	}
	g->map.grid[k] = NULL;
}

int	get_width(t_game *g)
{
	int	i;
	int	j;
	int	longest;

	i = 0;
	longest = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
			j++;
		if (longest < j)
			longest = j;
		i++;
	}
	return (longest);
}

int	get_height(t_game *g)
{
	int	i;

	i = 0;
	while (g->map.grid[i])
		i++;
	return (i);
}

void	get_dir(char dir, t_game *g)
{
	if (dir == 'N')
	{
		g->player.dir = 4.71238898;
	}
	else if (dir == 'S')
	{
		g->player.dir = 1.570796327;
	}
	else if (dir == 'W')
	{
		g->player.dir = 0;
	}
	else if (dir == 'E')
	{
		g->player.dir = 3.141592654;
	}
}

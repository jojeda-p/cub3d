/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 14:58:04 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/08/19 16:05:39 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static int	check_map_tail(char **matrix, int start)
{
	int	i;
	int	len;

	i = start;
	while (matrix[i])
	{
		if (matrix[i][0] == '\n' && matrix[i][1] == '\0')
			return (print_error(21, NULL));
		i++;
	}
	if (i == start)
		return (print_error(19, NULL));
	len = ft_strlen(matrix[i - 1]);
	if (len > 0 && matrix[i - 1][len - 1] == '\n')
		return (print_error(21, NULL));
	return (0);
}

static int	map_char_parse(char **matrix, t_game *g)
{
	int	i;
	int	j;

	i = g->map.init;
	while (matrix[i] && !(matrix[i][0] == '\n'
		&& matrix[i][1] == '\0'))
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] != '0' && matrix[i][j] != '1'
				&& matrix[i][j] != 'N' && matrix[i][j] != 'S'
				&& matrix[i][j] != 'E' && matrix[i][j] != 'W'
				&& matrix[i][j] != ' ' && matrix[i][j] != '\n')
				return (print_error(10, "map"));
			if (matrix[i][j] == 'N' || matrix[i][j] == 'S'
				|| matrix[i][j] == 'W' || matrix[i][j] == 'E')
				g->map.spawn++;
			j++;
		}
		i++;
	}
	if (g->map.spawn != 1)
		return (print_error(12, NULL));
	return (0);
}

static int	matrix_to_grid(char **matrix, t_game *g)
{
	int	i;
	int	j;
	int	k;

	if (malloc_grid(matrix, g) != 0)
		return (print_error(16, NULL));
	i = g->map.init;
	k = 0;
	while (matrix[i] && !(matrix[i][0] == '\n'
		&& matrix[i][1] == '\0'))
	{
		j = 0;
		while (matrix[i][j] && matrix[i][j] != '\n')
		{
			g->map.grid[k][j] = matrix[i][j];
			j++;
		}
		g->map.grid[k][j] = '\0';
		i++;
		k++;
	}
	g->map.grid[k] = NULL;
	return (0);
}

void	get_player(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			if (g->map.grid[i][j] == 'N' || g->map.grid[i][j] == 'S'
				|| g->map.grid[i][j] == 'W' || g->map.grid[i][j] == 'E')
			{
				g->player.y = (double)i + 0.5;
				g->player.x = (double)j + 0.5;
				get_dir(g->map.grid[i][j], g);
				g->map.grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	parse_map(char **matrix, t_game *g)
{
	g->map.spawn = 0;
	if (check_map_tail(matrix, g->map.init) != 0)
		return (1);
	if (map_char_parse(matrix, g) == 1)
		return (1);
	if (matrix_to_grid(matrix, g) == 1)
		return (1);
	if (init_map(g) == 1)
	{
		free_matrix(g->map.grid);
		g->map.grid = NULL;
		return (1);
	}
	if (parse_flood_fill(g) == 1)
	{
		free_matrix(g->map.grid);
		g->map.grid = NULL;
		return (1);
	}
	return (0);
}

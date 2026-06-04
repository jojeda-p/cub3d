/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 14:58:04 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 16:45:20 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_char_parse(char **matrix)
{
	int	i;
	int	j;

	i = 8;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] != ' ' || matrix[i][j] != '0' ||
				matrix[i][j] != '1' || matrix[i][j] != 'N' ||
				matrix[i][j] != '\n')
				return (print_error(10, "map"));
			j++;
		}
		i++;
	}
	return (0);
}

void	malloc_grid(char **matrix, t_game *g)
{
	int		i;
	int		j;
	int		longest;

	i = 0;
	while (matrix[i])
		i++;
	g->map.grid = malloc(sizeof(char *) * (i - 8));
	i = 0;
	longest = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
			j++;
		if (longest < j)
			longest = j;
		i++;
	}
	i = 0;
	while (matrix[i])
	{
		g->map.grid[i] = malloc(sizeof(char) * longest);
		i++;
	}
}

int	matrix_to_grid(char **matrix, t_game *g)
{
	int	i;
	int	j;

	malloc_grid(matrix, g);
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			
			j++;
		}
		i++;
	}
}

int	parse_map(char **matrix, t_game *g)
{
	if (map_char_parse(matrix) == 1)
		return (1);
	if (matrix_to_grid == 1)
		return (1);
}

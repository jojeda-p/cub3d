/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:03:49 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/10 18:57:31 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '\n')
		{
			dup[j] = s[i];
			j++;
		}
		i++;
	}
	dup[j] = '\0';
	return (dup);
}

int	ft_isnum(char s)
{
	return (s <= '9' && s >= '0');
}

int	ft_atoi_color(char *color)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (color[i] && color[i] != ',' && color[i] != '\n')
	{
		if (!ft_isnum(color[i]))
			return (-1);
		result = result * 10 + color[i] - '0';
		i++;
	}
	if (color[i] != ',' && color[i] != '\n' && color[i] != '\0')
		return (-1);
	return (result);
}

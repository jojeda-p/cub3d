/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:32:41 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 14:51:15 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

/*pone el path en la estructura final y comprueba que no se repita la textura*/
int	get_texture_path(t_game *g, char *s, char *path)
{
	if (s[0] == 'N' && g->tex[0].found == 0)
	{
		g->tex[0].path = path;
		g->tex[0].found = 1;
		return (0);
	}
	else if (s[0] == 'S' && g->tex[1].found == 0)
	{
		g->tex[1].path = path;
		g->tex[1].found = 1;
		return (0);
	}
	else if (s[0] == 'E' && g->tex[2].found == 0)
	{
		g->tex[2].path = path;
		g->tex[2].found = 1;
		return (0);
	}
	else if (s[0] == 'W' && g->tex[3].found == 0)
	{
		g->tex[3].path = path;
		g->tex[3].found = 1;
		return (0);
	}
	return (print_error(8, s));
}

int	parse_texture_name(char *path)
{
	int	len;

	if (!path)
		return (1);
	len = ft_strlen(path);
	if (len < 4 || path[len - 4] != '.'
		|| path[len - 3] != 'x'
		|| path[len - 2] != 'p'
		|| path[len - 1] != 'm')
		return (1);
	return (0);
}

char	*clean_path(char *path)
{
	char	*new;
	int		start;
	int		end;
	int		i;

	if (!path)
		return (NULL);
	start = 0;
	while (path[start] == ' ' || path[start] == '\t')
		start++;
	end = ft_strlen(path);
	while (end > start
		&& (path[end - 1] == ' ' || path[end - 1] == '\t'))
		end--;
	new = malloc(sizeof(char) * (end - start + 1));
	if (!new)
		return (free(path), NULL);
	i = 0;
	while (start < end)
		new[i++] = path[start++];
	new[i] = '\0';
	free(path);
	return (new);
}

static void	skip_spaces(char *color, int *i)
{
	while (color[*i] == ' ' || color[*i] == '\t')
		(*i)++;
}

int	get_component(char *color, int *i, int *value)
{
	int	digits;

	digits = 0;
	*value = 0;
	skip_spaces(color, i);
	while (ft_isnum(color[*i]))
	{
		*value = (*value * 10) + color[*i] - '0';
		if (*value > 255)
			return (1);
		(*i)++;
		digits++;
	}
	skip_spaces(color, i);
	if (digits == 0)
		return (1);
	return (0);
}

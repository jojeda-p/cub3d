/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:32:41 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 13:26:30 by jojeda-p         ###   ########.fr       */
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
	int	i;

	if (ft_strlen(path) < 4)
    	return (print_error(1, path));
	i = ft_strlen(path) - 1;
	if (path[i] != 'm' || path[i - 1] != 'p' || path[i - 2] != 'x'
		|| path[i - 3] != '.')
		return (print_error(1, path));
	return (0);
}

char	*clean_path(char *path)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (path[i] && (path[i] == ' ' || path[i] == '\t'))
		i++;
	j = i;
	while (path[j])
		j++;
	new = malloc(sizeof(char) * (j + 1));
	j = i;
	i = 0;
	while (path[j])
	{
		new[i] = path[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(path);
	return (new);
}

int	get_color_hex(char *color, char *s)
{
	int	r;
	int	g;
	int	b;
	int	i;

	r = ft_atoi_color(color);
	if (r == -1)
		return (print_error(9, s));
	i = 0;
	while (color[i] && ft_isnum(color[i]))
		i++;
	g = ft_atoi_color(color + i + 1);
	if (g == -1)
		return (print_error(9, s));
	i++;
	while (color[i] && ft_isnum(color[i]))
		i++;
	b = ft_atoi_color(color + i + 1);
	if (b == -1)
		return (print_error(9, s));
	return ((r << 16) | (g << 8) | b);
}

int check_color_number(char *color, char *s)
{
    int i;
	
	i = 0;
    while (color[i])
    {
        if (!ft_isnum(color[i]))
        {
            if (color[i+1] && !ft_isnum(color[i+1]) && color[i+2] && !ft_isnum(color[i+2]))
                return (print_error(9, s));
        }
        if (ft_isnum(color[i]) && color[i+1] && ft_isnum(color[i+1])
            && color[i+2] && ft_isnum(color[i+2]) && color[i+3] && ft_isnum(color[i+3]))
            return (print_error(9, s));
            
        while (color[i] && ft_isnum(color[i]))
            i++;
        if (color[i])
            i++;
    }
    return (0);
}

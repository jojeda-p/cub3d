/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headline_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 15:01:56 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/15 15:02:59 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_textures(t_game *g)
{
	if (!g->tex[0].path)
		return (print_error(5, "NO"));
	if (!g->tex[1].path)
		return (print_error(5, "SO"));
	if (!g->tex[2].path)
		return (print_error(5, "EA"));
	if (!g->tex[3].path)
		return (print_error(5, "WE"));
	if (!g->config.ceiling_color)
		return (print_error(6, "C"));
	if (!g->config.ceiling_color)
		return (print_error(6, "F"));
	return (0);
}

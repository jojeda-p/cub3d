/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:44:01 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/01 13:06:07 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2 || !argv[1])
		return (0);
	g = (t_game){0};//inicilizacion a 0 de toda la estructura
	g.height = 1000;
	g.width = 1500;
	temp_init_map(&g, argv[1]);
	init_raycasting(&g);
	init_window(&g);
	return (0);
}
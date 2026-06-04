/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:44:01 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 12:57:13 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (0);
	init_game(&g);
	/* if (parser(argv[1], &g) == 1)
		return (1); */
	temp_init_map(&g, argv[1]);
	init_raycasting(&g);
	init_window(&g);
	return (0);
}
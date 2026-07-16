/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:44:01 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/16 14:33:47 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (print_error(11, NULL));
	if (init_game(&g) != 0)
		return (print_error(16, NULL));
	if (parser(argv[1], &g) == 1)
		return (free_game(&g), 1);
	init_raycasting(&g);
	if (init_window(&g) == -1)
		return (free_game(&g), 1);
	return (0);
}

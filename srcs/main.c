/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:44:01 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/10 18:44:01 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (print_error(11, argv[1]));
	init_game(&g);
	if (parser(argv[1], &g) == 1)
		return (1);
	init_raycasting(&g);
	init_window(&g);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:14:37 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/03 18:25:52 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(int	code, char *s)
{
	if (code == 1)
		return (printf("Error: %s has wrong file type.\n", s), 1);
	if (code == 2)
		return (printf("Error: %s permission denied.\n", s), 1);
	if (code == 3)
		return (printf("Error: %s file not found.\n", s), 1);
	if (code == 4)
		return (printf("Error: %s is a directory.\n", s), 1);
	if (code == 5)
		return (printf("Error: texture %s not found.\n", s), 1);
	if (code == 6)
		return (printf("Error: %s color not found.\n", s), 1);
}
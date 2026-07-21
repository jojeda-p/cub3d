/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 13:58:58 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/07/21 13:59:26 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include "mlx.h"

void	destroy_tex(t_game *g, t_tex *tex)
{
	if (g->mlx && tex->img)
		mlx_destroy_image(g->mlx, tex->img);
	tex->img = NULL;
	tex->addr = NULL;
}

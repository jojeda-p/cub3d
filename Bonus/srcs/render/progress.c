/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 13:41:46 by josu              #+#    #+#             */
/*   Updated: 2026/07/21 13:36:52 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include "mlx.h"

static int	progress_len(int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*get_progress_text(t_game *g)
{
	char	*counter;
	char	*total;
	char	*tmp;
	char	*tmp2;
	char	*text;

	counter = ft_itoa2(g->config.sprite_counter);
	total = ft_itoa2(g->config.sprite);
	if (!counter || !total)
		return (free(counter), free(total), NULL);
	tmp = ft_strjoin("PROGRESS : ", counter);
	free(counter);
	if (!tmp)
		return (free(total), NULL);
	tmp2 = ft_strjoin(tmp, " / ");
	free(tmp);
	if (!tmp2)
		return (free(total), NULL);
	text = ft_strjoin(tmp2, total);
	free(tmp2);
	free(total);
	return (text);
}

static void	put_bold_string(t_game *g, int x, int y, char *str)
{
	mlx_string_put(g->mlx, g->win, x + 2, y + 2, 0x00000000, str);
	mlx_string_put(g->mlx, g->win, x - 1, y, 0x00FF6600, str);
	mlx_string_put(g->mlx, g->win, x + 1, y, 0x00FF6600, str);
	mlx_string_put(g->mlx, g->win, x, y - 1, 0x00FF6600, str);
	mlx_string_put(g->mlx, g->win, x, y + 1, 0x00FF6600, str);
	mlx_string_put(g->mlx, g->win, x, y, 0x00FFFFFF, str);
}

void	draw_progress(t_game *g)
{
	char	*text;
	int		x;
	int		y;
	int		len;

	if (g->config.sprite <= 0)
		return ;
	text = get_progress_text(g);
	if (!text)
		return ;
	len = 11 + progress_len(g->config.sprite_counter)
		+ 3 + progress_len(g->config.sprite);
	x = (g->config.width - (len * 10)) / 2;
	y = 35;
	put_bold_string(g, x, y, text);
	free(text);
}

void	check_game_end(t_game *g)
{
	if (g->config.sprite <= 0)
		return ;
	if (g->config.sprite_counter >= g->config.sprite)
		g->state = STATE_END;
}

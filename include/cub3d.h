/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 17:39:39 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/05/28 12:00:17 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*addr-dirección base de la imagen en memoria, dónde empieza la imagen
line_len-número de bytes que ocupa una fila completa de la imagen, cuánto avanza una fila
bpp-bits per pixel, cuántos bits ocupa cada píxel*/
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
    char	**grid;    // la matriz (array de strings)
    int		width;     // ancho en tiles
    int		height;    // alto en tiles
    int		tile_size; // tamaño en píxeles de cada tile
}	t_map;

/*por que se usan double- Permiten posiciones y velocidades fraccionarias (sub‑píxel)
 para acumular movimiento suave sin perder la parte decimal.
Ofrecen la precisión necesaria para ángulos/trigonometría y para multiplicar por delta time,
 evitando truncamientos y jitter.*/
typedef struct s_g
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
	int		width;
	int		height;
	double player_x;
	double player_y;
	double player_dir;
	double move_speed;
	double rot_speed;
}	t_game;

/* window.c */
int	init_window(t_game *data);
int	close_window(t_game *data);
int	key_hook(int keycode, t_game *data);

/* map.c */
int	temp_init_map(t_game *g, char *file);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 17:39:39 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/01 13:37:26 by jojeda-p         ###   ########.fr       */
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

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_input
{
	int up;
	int down;
	int left;
	int right;
} t_input;

/*por que se usan double- Permiten posiciones y velocidades fraccionarias (sub‑píxel)
 para acumular movimiento suave sin perder la parte decimal.
Ofrecen la precisión necesaria para ángulos/trigonometría y para multiplicar por delta time,
 evitando truncamientos y jitter.*/
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
	t_ray	ray;
	t_input	input;
	int		width;
	int		height;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	cam_x;
	double	cam_y;
	double	player_dir;
	double	move_speed;
	double	rot_speed;
}	t_game;

/*ray_init.c*/
void	init_raycasting(t_game *g);
double	calculate_camera_x(int column, int width);
void	init_ray_values(t_game *g);
void	init_ray_values2(t_game *g);
void	dda_loop(t_game *g);
void	calculate_wall_projection(t_game *g);
void	draw_wall_column(t_game *g, int column);

/*raycasting.c*/
void	render_raycasting(t_game *g);

/* window.c */
int		init_window(t_game *data);
int		close_window(t_game *data);
int		key_hook(int keycode, t_game *data);
void	pixel_put(t_img *img, int x, int y, int color);

/* map.c */
int		temp_init_map(t_game *g, char *file);


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julepere <julepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 17:39:39 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/04 12:59:30 by julepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

typedef struct s_tex
{
	void	*img;
	char	*path;
	char	*addr;//dirección base donde comienza la imagen en memoria (es como un array plano)
	int		bpp;//bits per pixel (qué tan grande es cada color: 32 bits típicamente)
	int		line_len;//bytes por fila (importante: puede no ser exacto ancho × bpp por alineación)
	int		endian;
	int		width;
	int		height;
}	t_tex;

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
	int arrow_left;
	int arrow_right;
} t_input;

/*por que se usan double- Permiten posiciones y velocidades fraccionarias (sub‑píxel)
 para acumular movimiento suave sin perder la parte decimal.
Ofrecen la precisión necesaria para ángulos/trigonometría y para multiplicar por delta time,
 evitando truncamientos y jitter.
tex[0] → norte
tex[1] → sur
tex[2] → este
tex[3] → oeste*/
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_tex	tex[4];//0->NORTE,1->SUR,2->ESTE,3->OESTE
	t_map	map;
	t_ray	ray;
	t_input	input;
	int		width;
	int		height;
	int		floor_color;
	int		ceiling_color;
	/*mouse temporalmente aqui*/
	int		mouse_x;
	int		mouse_y;
	int		last_mouse_x;
	int		mouse_warped;

	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	cam_x;
	double	cam_y;
	double	player_dir;
	double	move_speed;
	double	rot_speed;
	double	mouse_sensitivity;
}	t_game;

/*init.c*/
void	init_game(t_game *g);

/*ray_init.c*/
void	init_raycasting(t_game *g);
double	calculate_camera_x(int column, int width);
void	init_ray_values(t_game *g);
void	init_ray_values2(t_game *g);
void	dda_loop(t_game *g);
void	calculate_wall_projection(t_game *g);
void	draw_wall_column(t_game *g, int column, t_tex texture);

/*raycasting.c*/
void	render_raycasting(t_game *g);


/* window.c */
int		init_window(t_game *data);
int		close_window(t_game *data);
int		key_hook(int keycode, t_game *data);
void	pixel_put(t_img *img, int x, int y, int color);

/* map.c */
int		temp_init_map(t_game *g, char *file);

/*input*/
int		key_press(int keycode, t_game *g);
int		key_release(int keycode, t_game *g);


/* movement.c */
void	move_forward(char c, t_game *g);
void	move_backward(char c, t_game *g);
void	move_left(char c, t_game *g);
void	move_right(char c, t_game *g);
void	rotate_camera(double angle, t_game *g);
void	update_player(t_game *g);

/* texture.c */
t_tex	get_wall_texture(t_game *g);
int		get_tex_color(t_tex texture,int tex_x, int tex_y);
int		get_tex_x(t_game *g, t_tex texture);
void	load_textures(t_game *g);

/* utils.c */
int		ft_strlen(char *s);
void	free_matrix(char **matrix);
char	*ft_strdup(char *s);
int		parse_permisions(char	*file);

/* parse.c */
int		parser(char *file, t_game *g);

/*parse_headline.c*/
int		parse_headline(char **matrix, t_game *g);

/* parse_matrix.c */
char	**parse_content(char *file);

/* parse_error.c */
int		print_error(int	code, char *s);

#endif

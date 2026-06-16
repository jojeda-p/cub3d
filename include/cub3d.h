/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojeda-p <jojeda-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 17:39:39 by jojeda-p          #+#    #+#             */
/*   Updated: 2026/06/16 16:14:07 by jojeda-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                 ENUMS                                      */
/* ************************************************************************** */

typedef enum e_state
{
    STATE_GAME,
    STATE_PAUSE,
}   t_state;

/* ************************************************************************** */
/*                                 STRUCTS                                    */
/* ************************************************************************** */

/*
---------------------------------------------------------------------------------
	t_img — framebuffer de renderizado
		addr     : dirección base de la imagen en memoria
		line_len : bytes por fila (cuánto avanza una fila)
		bpp      : bits per pixel
*/
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/*
---------------------------------------------------------------------------------
	t_tex — textura de pared
		addr     : array plano con los píxeles de la imagen
		bpp      : bits per pixel (típicamente 32)
		line_len : bytes por fila
*/
typedef struct s_tex
{
	void	*img;
	char	*path;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		found;
}	t_tex;

/*
---------------------------------------------------------------------------------
	t_map — mapa del nivel
		grid      : matriz de strings
		width     : ancho en tiles
		height    : alto en tiles
		tile_size : tamaño en píxeles de cada tile
*/
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		tile_size;
	int		init;
	int		anim;
	int		door;
	int		spawn;
	int		open;
}	t_map;

/*
---------------------------------------------------------------------------------
	t_ray — estado del rayo activo por columna
		camera_x		: ???
		ray_dir_x/y		: Vector de direccion del rayo (dir + plane * camera_x)
		delta_dist_x/y	: Distancia del rayo entre dos lineas del grid de la
						   misma direccion (X o Y)
		side_dist X/Y	: Distancia desde la posicion actual del jugador hasta
						   la primera linea del grid (X o Y)
		perp_dist		: Distancia perpendicular al plano de cámara hasta el
						   muro (NO distancia euclídea — evita el fish-eye effect)
		map_x/y			: Celda del mapa donde esta el rayo en cada paso del DDA
		step_x			: Dirección del paso DDA: +1 o -1 según ray_dir
		side			: Qué cara del muro fue golpeada — 0 = NS, 1 = EW
		hit				: Flag del bucle DDA, 1 = rayo ha chocado con un muro
		line_height		: Altura en píxeles de la columna de muro a dibujar
						   calculada como (HEIGHT / perp_dist)
		draw_start		: Píxel Y donde empieza a dibujarse la columna
		draw_end		: Píxel Y donde termina de dibujarse la columna
*/
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
	double	*z_buf;
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

/*
---------------------------------------------------------------------------------
	t_input — estado de teclas presionadas
*/
typedef struct s_input
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	arrow_left;
	int	arrow_right;
	int shift;
}	t_input;

/*
---------------------------------------------------------------------------------
	t_player — posición, dirección y físicas del jugador
		dir      : vector de dirección normalizado
		vel      : velocidad acumulada (para inercia)
*/
typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	double	dir_x;
	double	dir_y;	
	double	rot_speed;
	double	accel;
	double	max_speed;

	double	vel_x;
	double	vel_y;
	double	force;
	double	mass;
	double	friction;
	double	sprint_speed;
	double	walk_speed;
}	t_player;

/*
---------------------------------------------------------------------------------
	t_camera — plano de proyección y configuración visual
		cam    : vector perpendicular a dir (frustum del FOV)
		fov      : campo de visión en radianes (plane_len = tan(fov/2))
		sensitivity : velocidad de rotación con ratón
*/
typedef struct s_camera
{
	double	plane_x;
	double	plane_y;
	double	fov;
	double	walk_fov;
	double	sprint_fov;
	double	sensitivity;
	int		mouse_x;
	int		last_mouse_x;
	int		mouse_warped;
}	t_camera;

/*
---------------------------------------------------------------------------------
	t_minimap — 
		width / heigth : tamaño en pantalla en píxeles
		scale : píxeles del mundo por píxel del minimapa
		border : grosor del margen en píxeles
		offset_x/y : posición exacta del jugador en píxeles del minimapa,
		 incluyendo la fracción dentro del tile
*/
typedef struct s_minimap
{
    int		width;
    int     height;
    double	scale;
    int		border;
	double	offset_x;
	double	offset_y;
	double	margin_x;
	double	margin_y;
	double	inner_x;
    double	inner_y;
	int		player_tile_x;
	int		player_tile_y;
	int		map_x;
	int		map_y;
	int		visible_tiles;
    int		color_wall;
    int		color_floor;
    int		color_player;
	int		color_direction;
    int		color_border;
    int		color_void;
}   t_minimap;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	distance;
	t_tex	frames[16];
	int		num_frames;
	int		current_frame;
}	t_sprite;


/*
---------------------------------------------------------------------------------
	t_config — parámetros visuales modificables en init
		Centraliza todos los valores tuneable del juego.
*/
typedef struct s_config
{
	int	width;
	int	height;
	int	floor_color;
	int	ceiling_color;
	int	sprite;
	int	door;
	int	frame_counter;
	int	anim_speed;
}	t_config;

/*
---------------------------------------------------------------------------------
	t_game — estado global del juego
		tex[0] → norte | tex[1] → sur | tex[2] → este | tex[3] → oeste
		Se usan double para posición/dirección porque permiten movimiento
		sub-píxel suave, precisión trigonométrica y multiplicación por delta time
		sin truncamientos ni jitter.
*/
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_tex		tex[4];
	t_tex		pause_tex;
	t_map		map;
	t_ray		ray;
	t_input		input;
	t_player	player;
	t_camera	camera;
	t_config	config;
	t_minimap	mm;
	t_state		state;
	t_sprite	*sprite;
}	t_game;

/* ************************************************************************** */
/*                               PROTOTYPES                                   */
/* ************************************************************************** */

/* init.c */
void	init_game(t_game *g);

/* window.c */
int		init_window(t_game *g);
int		close_window(t_game *g);
int		key_hook(int keycode, t_game *g);
void	pixel_put(t_img *img, int x, int y, int color);

/* input.c */
int		key_press(int keycode, t_game *g);
int		key_release(int keycode, t_game *g);

/* movement.c */
void	rotate_camera(double angle, t_game *g);
void	update_player(t_game *g);

/* directions.c */
void	move_forward(t_game *g);
void	move_backward(t_game *g);
void	move_right(t_game *g);
void	move_left(t_game *g);
double  update_mouse(t_game *g);

/* raycasting.c */
void	render_raycasting(t_game *g);

/* ray_init.c */
void	init_raycasting(t_game *g);
double	calculate_camera_x(int column, int width);
void	init_ray_values(t_game *g);
void	init_ray_values2(t_game *g);


/* texture.c */
void	load_textures(t_game *g);
t_tex	get_wall_texture(t_game *g);
int		get_tex_x(t_game *g, t_tex texture);
int		get_tex_color(t_game *g, t_tex texture, int tex_x, int tex_y);

/* map.c */
int		temp_init_map(t_game *g, char *file);

/* minimap.c */
void	draw_minimap(t_game *g);

/* minimap_utils.c */
void	draw_border(t_game *g, int x, int y);
int		div_floor(int a, int b);
void	draw_tiles(t_game *g, int x, int y);

/* parse.c */
int		parser(char *file, t_game *g);

/* parse_headline.c */
int		parse_headline(char **matrix, t_game *g);

/* parse_headline_utils.c */
int		get_texture_path(t_game *g, char *s, char *path);
int		parse_texture_name(char *path);
char	*clean_path(char *path);
int		get_color_hex(char *color, char *s);
int		check_color_number(char *color, char *s);

/* parse_map.c */
int		parse_map(char **matrix, t_game *g);

/* parse_map_2.c */
int		parse_flood_fill(t_game *g);

/* parse_map_utis.c */
int		valid_char(char c);
void	malloc_grid(char **matrix, t_game *g);
int		get_width(t_game *g);
int		get_height(t_game *g);
void	get_dir(char dir, t_game *g);

/* parse_matrix.c */
char	**parse_content(char *file);

/* parse_error.c */
int		print_error(int code, char *s);

/* utils.c */
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
void	free_matrix(char **matrix);
int		parse_permisions(char *file);
int		ft_atoi_color(char *color);
int		ft_isnum(char s);

/* sprites.c */
void	load_sprite(t_game *g);
void    load_sprite_textures(t_game *g);
void	render_sprites(t_game *g);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:11:07 by tbertozz          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/09 16:00:06 by tbertozz         ###   ########.fr       */
=======
/*   Updated: 2023/02/09 15:53:36 by jwilliam         ###   ########.fr       */
>>>>>>> 6f8ab23f5d39670f114c73bbcb4f4061de0f7bd5
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
Includes
*/
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

/*
MLX window settings
*/
# define WIN_WIDTH		1280
# define WIN_HEIGHT		720
# define WIN_TITLE		"cub3D"
# define WALL_HEIGHT	128
# define TEX_WIDTH		128
# define TEX_HEIGHT		128

/*
MLX Key codes
*/
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_W	 		13
# define KEY_ESC 		53
# define KEY_LEFT 		123
# define KEY_RIGHT 		124
# define KEY_DOWN 		125
# define KEY_UP 		126

/*
Math schidt
*/
# define PI				3.142857

/*
FOV
*/
# define FOV			60

/* Tile Types */
typedef enum e_tiletype
{
	BLANK = ' ',
	FLOOR = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W'
}	t_tiletype;

/* struct for numbers because norm */
typedef struct s_number
{
	int	x;
	int	y;
}	t_number;

/* X and Y direction */
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/* vector struct */
typedef struct s_pvector
{
	double	x;
	double	y;
}	t_pvector;

/* Tile */
typedef struct s_tile
{
	t_tiletype		type;
	t_tiletype		og_type;
	t_vector		position;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
}	t_tile;

/* Color */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

/* An image that covers the whole window */
typedef struct s_panel
{
	void		*pointer;
	char		*pixels;
	t_vector	size;
	int			bpp;
	int			line_size;
	int			endian;
}	t_panel;

/* Image struct */
typedef struct s_images
{
	void	*pointer;
	char	*address;
	int		width;
	int		height;
	int		l_size;
	int		bpp;
	int		endian;
}	t_images;

/* Struct that holds the textures for the walls and ceiling*/
typedef struct s_mapdata
{
	char	*no;
	void	*northimg;
	char	*so;
	void	*southimg;
	char	*ea;
	void	*eastimg;
	char	*we;
	void	*westimg;
	int		c[3];
	int		f[3];
	int		max_width;
	int		max_height;
	int		player_exists;
}	t_mapdata;

/* Struct that is used for texturing the walls */
typedef struct s_exture_wall
{
	double	x;
	double	y;
	double	dx;
	double	dy;
}	t_exture_wall;

/* Player Struct */
typedef struct s_player
{
	int			height;
	t_pvector	direction;
	t_pvector	strafe;
	double		speed;
	double		x;
	double		y;
	double		plane_x;
	double		plane_y;
	int			ismovef;
	int			ismoveb;
	int			isstrl;
	int			isstrr;
	int			isrotl;
	int			isrotr;
}	t_player;

/* Ray Struct */
typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			side;
	double		wall_distance;
	double		wall_normal;
	char		*wall_texture;
	int			wall_colour;
	double		wall_x;
	int			wallheight;
	int			draw_start;
	int			draw_end;
	void		*texture;
	int			hit;
	int			beam_pos_x;
	int			beam_pos_y;
	int			step_x;
	int			step_y;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
}	t_ray;

/* Main Struct */
typedef struct s_game
{
	void		*mlx;
	void		*mlx_window;
	t_vector	window_size;
	t_tile		**tilemap;
	t_images	*img;
	t_mapdata	mapdata;
	char		**file;
	t_player	doom_guy;
	t_ray		rayban;
}	t_game;

/* close_game.c */
int			close_win(t_game *game);

/* draw_beegee.c */
void		draw_bg(t_game *game);
int			create_rgb(int r, int g, int b);

/* error.c */
void		print_error(int code, char *str);

/* floodfill.c */
int			floodfill_tile_check(t_game *game, int y, int x, t_tile **tilemap);
int			perform_floodfill(t_game *game, t_tile **tilemap);

/* free.c */
void		free_2d_array(char **array);
void		free_tilemap(t_game *game);

/* imageload.c */
void		imageload(t_game *game);

/* init_img.c */
int			init_image(t_game *game);

/* init_mlx.c */
void		start_mlx(t_game *game);

/* init_player.c */
int			init_player(t_game *game);
void		init_other(t_game *game);

/* key_input.c */
int			key_input(int key, void *param);
int			key_release(int key, void *param);
void		move_guy(int key, t_game *game);

/* loops.c */
int			main_loop(t_game *game);

/* map_check_utils.c */
int			iswhitespace(int i, char *mapfile);
int			skip_lines(t_game *game);
int			count_height(t_game *game, int skip);
int			count_width(t_game *game, int skip);

/* map_check_utils2.c */
int			check_tile_skip(t_tiletype tile);
void		check_tile_player(t_game *game, t_tiletype tile);
int			check_tile_floor(t_tiletype tile);
int			check_adjacent_tile(t_tile **tilemap, int y, int x);

/* map_check_utils3.c */
int			savelines(t_game *game, int x, int y, t_tile **tilemap);
void		incrementator(t_game *game, t_number num, t_tile **tilemap,
				int skip);

/* map_check.c */
t_tiletype	define_tiletype(char definer);
void		setup_tile(t_tile **tilemap, int y, int x, t_game *game);
t_tile		**generate_tilemap(t_game *game);

/* map_file_check.c */
void		initialise_struct(t_mapdata *mapdata);
int			charcheck(int i, t_game *game, char *file);
int			check_map_settings(t_game *game);
int			init_check(t_game *game);

/* map_file_check_utils.c */
int			add_texture(int i, char *file, t_game *game, int id);
int			set_colors(int i, char *file, t_game *game, int id);

/* mlx_hooks.c */
void		set_mlx_hooks(t_game *game);

/* movement.c */
int			move_loop(t_game *game);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		strafe_left(t_game *game);
void		strafe_right(t_game *game);

/* raycasting.c */
void		raycast(t_game *game);
void		set_raycast_initial(t_game *game, int ray, t_ray *ray_stuff);
void		shoot_ray(t_game *game, t_ray *ray_stuff);
void		set_ray_direction(t_game *game, t_ray *ray_stuff);
void		set_walls(t_game *game, t_ray *ray_stuff);

/* raycasting2.c */
void		texture_wall(t_game *game, int x, t_ray *ray);
void		draw_wall(t_game *game, int x, t_ray *aray);

/* raycasting_utils.c */
void		put_pixel(t_images *image, int x, int y, int colour);
void		*texture_picker(t_game *game, t_ray *ray_stuff);

/* rotation.c */
t_pvector	do_rotate(t_pvector vector, double rotate);
void		rotate_right(t_game *game);
void		rotate_left(t_game *game);

/* tilemap_generator.c */
int			read_map(char *file, t_game *game);
#endif
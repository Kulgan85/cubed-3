/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:07:15 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/19 13:50:54 by tbertozz         ###   ########.fr       */
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

/*
MLX window settings
*/
# define WIN_WIDTH		1280
# define WIN_HEIGHT		720
# define WIN_TITLE		"cub3d"

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

/* X and Y direction */
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

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

/* Image struct */
typedef struct s_images
{
	void	*image;
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
	char	*so;
	char	*ea;
	char	*we;
	int		c[3];
	int		f[3];
	int		max_width;
	int		max_height;
}	t_mapdata;

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
}	t_game;

/* close_game.c */
int			close_win(t_game game);

/* error.c */
void		print_error(int code, char *str);

/* init_mlx.c */
void		start_mlx(t_game *game);

/* key_input.c */
int			key_input(int key, void *param);

/* map_check_utils.c */
void		free_2d_array(char **array);
int			iswhitespace(int i, char *mapfile);

/* map_check.c */
int			floodfill_tile_check(t_game *game, int x, int y, t_tile **tilemap);
t_tiletype	define_tiletype(char definer);
void		setup_tile(t_tile **tilemap, int x, int y, t_game *game);
t_tile		**generate_tilemap(char **map, t_game *game);

/* map_file_check.c */
int			add_texture(int i, char *file, t_game *game, int id);
int			set_colors(int i, char *file, t_game *game, int id);
void		initialise_struct(t_mapdata *mapdata);
int			charcheck(int i, t_game *game, char *file);
int			init_check(t_game *game);

/* mlx_hooks.c */
void		set_mlx_hooks(t_game game);

/* tilemap_generator.c */
int			read_map(char *file, t_game *game);
int			map_init_check(t_game *game, char *map);

#endif
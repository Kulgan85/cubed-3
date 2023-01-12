/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:07:15 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/12 16:16:01 by tbertozz         ###   ########.fr       */
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
# define KEY_ESC 		53
# define KEY_LEFT 		123
# define KEY_RIGHT 		124
# define KEY_DOWN 		125
# define KEY_UP 		126

/* Tile Types */
typedef enum e_tiletype
{
	BLANK = ' ',
	EMPTY = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W'
}	t_tiletype;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/* Tile */
typedef struct s_tile
{
	t_tiletype	type;
	t_tiletype	og_type;
	t_vector	*position;
}	t_tile;

/* Color */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

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

/* Main Struct */
typedef struct s_game
{
	void		*mlx;
	void		*mlx_window;
	t_vector	window_size;
	t_tile		**tilemap;
	t_images	*img;
	t_mapdata	mapdata;
}	t_game;

typedef struct s_mapdata
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		c[3];
	int		f[3];
}	t_mapdata;

#endif
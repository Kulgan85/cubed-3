/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:07:15 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/12 12:00:10 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


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

typedef struct s_tile
{
	t_tiletype	type;
	t_tiletype	og_type;
	t_vector	*position;
}	t_tile;

typedef struct s_game
{
	t_tile	**tilemap;
}	t_game;
#endif

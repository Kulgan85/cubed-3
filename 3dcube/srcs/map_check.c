/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:20:04 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/13 16:37:39 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* "Flood fill" the map */
int	floodfill_single_tile_check(t_game *game, int x, int y)
{
	if (game->tilemap[x][y].type == BLANK
	&& game->tilemap[x][y].up->type != EMPTY
	&& game->tilemap[x][y].down->type != EMPTY
	&& game->tilemap[x][y].left->type != EMPTY
	&& game->tilemap[x][y].right->type != EMPTY)
		printf("good");
	else
	{
		printf("bad");
	}
	return (1);
}

/* Returns the tiletype that corresponds to <definer> */
t_tiletype	define_tiletype(char definer)
{
	if (definer == '1')
		return (WALL);
	if (definer == '0')
		return (BLANK);
	if (definer == 'N')
		return (NORTH);
	if (definer == 'E')
		return (EAST);
	if (definer == 'w')
		return (WEST);
	else if (definer == 'S')
		return (SOUTH);
	return (EMPTY);
}

/* Set the size, original type and neighboors of the <x><y> tile of <tilemap> */
void	setup_tile(t_tile **tilemap, int x, int y)
{
	tilemap[y][x].og_type = tilemap[y][x].type;
	tilemap[y][x].position->x = x;
	tilemap[y][x].position->y = y;
	if (y != 0)
		tilemap[y][x].up = &tilemap[y - 1][x];
	if (tilemap[y + 1] != NULL)
		tilemap[y][x].down = &tilemap[y + 1][x];
	if (x != 0)
		tilemap[y][x].left = &tilemap[y][x - 1];
	tilemap[y][x].right = &tilemap[y][x + 1];
}

/* Returns a t_tile table filled according to map,
each line ends in a tile of type 0,
columns ends in a NULL pointer */
t_tile	**generate_tilemap(char **map, t_game *game)
{
	t_tile		**tilemap;
	int			x;
	int			y;

	tilemap = alloc_tilemap(map);
	if (!tilemap)
		return (null_error("malloc error on alloc_tilemap()"));
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			tilemap[y][x].type = define_tiletype(map[y][x]);
			setup_tile(tilemap, x, y);
			floodfill_single_tile_check(game, x, y);
			x++;
		}
		tilemap[y][x].type = 0;
		y++;
	}
	tilemap[y] = NULL;
	return (tilemap);
}

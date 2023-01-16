/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:20:04 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/16 13:11:06 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* "Flood fill" the map */
int	floodfill_single_tile_check(t_game *game, int x, int y)
{
	if (game->tilemap[x][y].type == BLANK ||
			game->tilemap[x][y].type == NORTH ||
			game->tilemap[x][y].type == SOUTH ||
			game->tilemap[x][y].type == EAST ||
			game->tilemap[x][y].type == WEST &&
			game->tilemap[x][y].up->type != EMPTY &&
			game->tilemap[x][y].down->type != EMPTY &&
			game->tilemap[x][y].left->type != EMPTY &&
			game->tilemap[x][y].right->type != EMPTY)
	{
		dprintf(2, "good");
	}
	else
	{
		print_error(3, " - Flood Fill Failure");
		return (0);
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
	if (definer == 'W')
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
		printf("malloc error on alloc_tilemap()");
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[x][y] != '\0')
		{
			tilemap[x][y].type = define_tiletype(map[y][x]);
			printf(tilemap[x][y].type);
			setup_tile(tilemap, x, y);
			x++;
		}
		tilemap[y][x].type = 0;
		y++;
	}
	y = 0;
	printf("Check");
	while (map[y])
	{
		x = 0;
		while (map[x][y] != '\0')
		{
			printf("FLOOD FILL CHECK");
			floodfill_single_tile_check(game, x, y);
			x++;
		}
		y++;
	}
	printf("FLood fill complete");
	tilemap[y] = NULL;
	return (tilemap);
}

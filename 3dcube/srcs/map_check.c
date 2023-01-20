/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:20:04 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/20 11:44:39 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Perform a lazy flood fill on the map */
int	floodfill_tile_check(t_game *game, int x, int y, t_tile **tilemap)
{
	printf("Start Flooding with tile x: %d y: %d\n", x, y);
	if (&tilemap[x][y])
	{
		printf("Exists with type of %d\n", tilemap[x][y].type);
	}
	if (x == 0 || x == game->mapdata.max_width || y == 0
		|| y == game->mapdata.max_height)
	{
		if (tilemap[x][y].type != WALL && tilemap[x][y].type != BLANK)
			print_error(3, "Flood Fill Failure\n");
	}
	if (tilemap[x][y].type == WALL || tilemap[x][y].type == '\0'
		|| tilemap[x][y].type == BLANK)
		return (1);
	if (
		(tilemap[x][y].type == FLOOR
		|| tilemap[x][y].type == NORTH
		|| tilemap[x][y].type == SOUTH
		|| tilemap[x][y].type == EAST
		|| tilemap[x][y].type == WEST)
		&&
		(tilemap[x][y].up != NULL && tilemap[x][y].up->type != BLANK) &&
		(tilemap[x][y].down != NULL && tilemap[x][y].down->type != BLANK) &&
		(tilemap[x][y].left != NULL && tilemap[x][y].left->type != BLANK) &&
		(tilemap[x][y].right != NULL && tilemap[x][y].up->type != BLANK))
	{
		printf("Good Fill\n");
	}
	else
	{
		print_error(3, "Flood Fill Failure\n");
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
		return (FLOOR);
	if (definer == 'N')
		return (NORTH);
	if (definer == 'E')
		return (EAST);
	if (definer == 'W')
		return (WEST);
	else if (definer == 'S')
		return (SOUTH);
	return (BLANK);
}

/* Set the size, original type and neighboors of the <x><y> tile of <tilemap> */
void	setup_tile(t_tile **tilemap, int x, int y, t_game *game)
{
	tilemap[y][x].og_type = tilemap[y][x].type;
	tilemap[y][x].position.x = x;
	tilemap[y][x].position.y = y;
	if (y > 0)
		tilemap[y][x].up = &tilemap[y - 1][x];
	else
		tilemap[y][x].up = NULL;
	if (y < game->mapdata.max_height)
		tilemap[y][x].down = &tilemap[y + 1][x];
	else
		tilemap[y][x].down = NULL;
	if (x > 0)
		tilemap[y][x].left = &tilemap[y][x - 1];
	else
		tilemap[y][x].left = NULL;
	if (x < game->mapdata.max_width)
		tilemap[y][x].right = &tilemap[y][x + 1];
	else
		tilemap[y][x].right = NULL;
}

t_tile	**alloc_tilemap(int skip, t_game *game)
{
	int		i;
	t_tile	**new;

	i = 0;
	printf("%s\n", game->file[skip + i]);
	while (game->file[skip + i] != 0)
		i++;
	new = malloc(sizeof(t_tile *) * game->mapdata.max_height);
	if (!new)
		return (NULL);
	i = 0;
	while (game->file[skip + i] != NULL)
	{
		new[i] = malloc(sizeof(t_tile) * game->mapdata.max_width);
		if (new == NULL)
		{
			while (i > 0)
				free(new[i--]);
			return (NULL);
		}
		i++;
	}
	return (new);
}

/* Returns a t_tile table filled according to map,
columns ends in a NULL pointer */
t_tile	**generate_tilemap(char **map, t_game *game)
{
	t_tile		**tilemap;
	int			x;
	int			y;
	int			skip;

	(void)map;
	printf("Start skipping lines\n");
	skip = skip_lines(game);
	game->mapdata.max_height = (count_height(game, skip) - 1);
	printf("map max height %i\n", game->mapdata.max_height);
	game->mapdata.max_width = (count_width(game, skip) - 1);
	printf("map max width %i\n", game->mapdata.max_width);
	tilemap = alloc_tilemap(skip, game);
	if (!tilemap)
		printf("malloc error on alloc_tilemap()");
	y = 0;
	while (game->file[skip + y] && y < game->mapdata.max_height)
	{
		x = 0;
		while (x < game->mapdata.max_width)
		{
			printf("Loop number - X: %d Y: %d\n", x, y);
			tilemap[x][y].type = define_tiletype(game->file[skip + y][x]);
			setup_tile(tilemap, x, y, game);
			x++;
		}
		y++;
	}
	printf("Tilemap set\n");
	if (perform_floodfill(game, tilemap) != 1)
		print_error(3, "Invalid map");
	printf("FLood fill complete");
	tilemap[y] = NULL;
	return (tilemap);
}

int	perform_floodfill(t_game *game, t_tile **tilemap)
{
	int	y;
	int	x;

	y = 0;
	printf("FLOOD FILL START\n");
	while (y < game->mapdata.max_height)
	{
		x = 0;
		while (x < game->mapdata.max_width)
		{
			floodfill_tile_check(game, x, y, tilemap);
			x++;
		}
		y++;
	}
	printf("Flood fill complete\n\n");
	return (1);
}

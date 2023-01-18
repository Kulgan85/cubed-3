/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:20:04 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/18 20:54:54 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* "Flood fill" the map */
int	floodfill_single_tile_check(t_game *game, int x, int y)
{
	if ((game->tilemap[x][y].type == BLANK ||
			game->tilemap[x][y].type == NORTH ||
			game->tilemap[x][y].type == SOUTH ||
			game->tilemap[x][y].type == EAST ||
			game->tilemap[x][y].type == WEST) &&
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

int	skip_lines(t_game *game)
{
	int			i;

	i = 0;
	while (ft_strtrim(game->file[i], " ")[0] != '1' &&
			ft_strtrim(game->file[i], " ")[0] != '0')
		i++;
	return (i);
}

int	count_height(t_game *game, int skip)
{
	int		i;

	i = 0;
	while (game->file[skip + i] != 0)
		i++;
	return (i);
}

int	count_width(t_game *game, int skip)
{
	int		max;
	int		i;
	int		j;

	max = 0;
	i = 0;
	j = 0;
	while (game->file[skip + i] != 0)
	{
		j = ft_strlen(game->file[skip + i]);
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

t_tile	**alloc_tilemap(int skip, t_game *game)
{
	int		i;
	t_tile	**new;

	i = 0;
	while (game->file[skip + i] != 0)
		i++;
	new = (t_tile **)malloc(sizeof(t_tile *) * i + 1);
	if (!new)
		return (NULL);
	return (new);
}

/* Returns a t_tile table filled according to map,
each line ends in a tile of type 0,
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
	game->mapdata.max_height = count_height(game, skip);
	printf("map max height %i\n", game->mapdata.max_height);
	game->mapdata.max_width = count_width(game, skip);
	printf("map max width %i\n", game->mapdata.max_width);
	tilemap = alloc_tilemap(skip, game);
	if (!tilemap)
		printf("malloc error on alloc_tilemap()");
	y = 0;
	while (game->file[skip + y])
	{
		x = 0;
		while (game->file[skip + y][x] != '\0')
		{
			tilemap[x][y].type = define_tiletype(game->file[skip + y][x]);
			printf("tile type %d\n", tilemap[x][y].type);
			setup_tile(tilemap, x, y);
			x++;
		}
		tilemap[y][x].type = 0;
		y++;
	}
	y = 0;
	printf("Check");
	while (y < game->mapdata.max_height)
	{
		x = 0;
		while (x < game->mapdata.max_width)
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

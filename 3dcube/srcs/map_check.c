/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:20:04 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 12:58:45 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Perform a lazy flood fill on the map */
int	floodfill_tile_check(t_game *game, int y, int x, t_tile **tilemap)
{
	printf("max height - %i, max width - %i\n", game->mapdata.max_height, game->mapdata.max_width);
	printf("wall type - %d\n", tilemap[y][y].type);
	if ((x == 0 || x == game->mapdata.max_width)
		|| (y == 0 || y == game->mapdata.max_height))
	{
		if (tilemap[y][x].type == WALL || tilemap[y][x].type == BLANK)
		{
			printf("is outer wall\n");
			return (1);
		}
		else
		{
			printf("is not outer wall\n");
			return (0);
		}
	}
	if (check_tile_skip(tilemap[y][x].type) == 0)
		return (1);
	if ((check_tile_floor(tilemap[y][x].type) == 0)
		&& (check_adjacent_tile(tilemap, y, x) == 0))
		return (1);
	else
		return (0);
}

/* Returns the tiletype that corresponds to <definer> */
t_tiletype	define_tiletype(char definer)
{
	if (definer == '1')
		return (WALL);
	else if (definer == '0')
		return (FLOOR);
	else if (definer == 'N')
		return (NORTH);
	else if (definer == 'E')
		return (EAST);
	else if (definer == 'W')
		return (WEST);
	else if (definer == 'S')
		return (SOUTH);
	return (BLANK);
}

/* Set the size, original type and neighboors of the <x><y> tile of <tilemap> */
void	setup_tile(t_tile **tilemap, int y, int x, t_game *game)
{
	tilemap[y][x].og_type = tilemap[y][x].type;
	tilemap[y][x].position.x = x;
	tilemap[y][x].position.y = y;
	printf("good");
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
	new = (t_tile **)malloc(sizeof(t_tile *) * game->mapdata.max_height + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (game->file[skip + i] != NULL)
	{
		printf("%d\n", game->mapdata.max_width);
		new[i] = (t_tile *)malloc(sizeof(t_tile) * game->mapdata.max_width + 1);
		if (new == NULL)
		{
			printf("Not malloc properly");
			while (i > 0)
				free(new[i--]);
			return (NULL);
		}
		printf("Malloc properly\n");
		printf("Loop number %i\n", i);
		i++;
	}
	printf("done allocating\n");
	return (new);
}

/* Returns a t_tile table filled according to map,
columns ends in a NULL pointer */
t_tile	**generate_tilemap(t_game *game)
{
	t_tile		**tilemap;
	int			x;
	int			y;
	int			skip;

	skip = skip_lines(game);
	game->mapdata.max_height = (count_height(game, skip));
	game->mapdata.max_width = (count_width(game, skip) - 1);
	tilemap = alloc_tilemap(skip, game);
	if (!tilemap)
		printf("malloc error on alloc_tilemap()\n");
	y = 0;
	while (game->file[skip + y] && y < game->mapdata.max_height)
	{
		x = 0;
		while (x < game->mapdata.max_width)
		{
			printf("%c\n", game->file[skip + y][x]);
			if (game->file[skip + y][x] == '\0'
				|| game->file[skip + y][x] == EOF)
			{
				while (x <= game->mapdata.max_width)
				{
					tilemap[y][x].type = BLANK;
					x++;
				}
			}
			else
			{
				tilemap[y][x].type = define_tiletype(game->file[skip + y][x]);
				setup_tile(tilemap, y, x, game);
				x++;
			}
		}

		y++;
	}
	if (perform_floodfill(game, tilemap) != 1)
		print_error(3, "Invalid map");
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
			printf("col %i, row %i\n", x, y);
			if (!(floodfill_tile_check(game, y, x, tilemap)))
			{
				printf("BAD\n");
				//brute_force_print_map(tilemap, game);
				return (0);
			}
			x++;
		}
		y++;
	}
	printf("Flood fill complete\n\n");
	return (1);
}

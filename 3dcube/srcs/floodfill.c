/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:31:09 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 15:32:03 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Perform a lazy flood fill on the map */
int	floodfill_tile_check(t_game *game, int y, int x, t_tile **tilemap)
{
	printf("max height - %i, max width - %i\n", game->mapdata.max_height,
		game->mapdata.max_width);
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
	check_tile_player(game, tilemap[y][x].type);
	if (check_tile_skip(tilemap[y][x].type) == 0)
		return (1);
	if ((check_tile_floor(tilemap[y][x].type) == 0)
		&& (check_adjacent_tile(tilemap, y, x) == 0))
		return (1);
	else
		return (0);
}

int	perform_floodfill(t_game *game, t_tile **tilemap)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->mapdata.max_height)
	{
		x = 0;
		while (x < game->mapdata.max_width)
		{
			printf("col %i, row %i\n", x, y);
			if (!(floodfill_tile_check(game, y, x, tilemap)))
			{
				printf("BAD\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	if (game->mapdata.player_exists == 0)
		print_error(2, "Bad map: No player");
	return (1);
}

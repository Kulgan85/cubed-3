/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:54 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 16:12:34 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_tile_skip(t_tiletype tile)
{
	if (tile == WALL || tile == '\0' || tile == BLANK)
		return (0);
	else
		return (1);
}

int	check_tile_floor(t_tiletype tile)
{
	if (tile == FLOOR || tile == NORTH || tile == SOUTH || tile == EAST
		|| tile == WEST)
		return (0);
	else
		return (1);
}

void	check_tile_player(t_game *game, t_tiletype tile)
{
	if (tile == NORTH || tile == SOUTH || tile == WEST || tile == EAST)
	{
		if (game->mapdata.player_exists == 1)
			print_error(2, "Bad Map: multiple players");
		game->mapdata.player_exists = 1;
	}
	return ;
}

int	check_adjacent_tile(t_tile **tilemap, int y, int x)
{
	if ((tilemap[y][x].up != NULL && tilemap[y][x].up->type != BLANK)
		&& (tilemap[y][x].down != NULL && tilemap[y][x].down->type != BLANK)
		&& (tilemap[y][x].left != NULL && tilemap[y][x].left->type != BLANK)
		&& (tilemap[y][x].right != NULL && tilemap[y][x].right->type != BLANK))
		return (0);
	else
		return (1);
}

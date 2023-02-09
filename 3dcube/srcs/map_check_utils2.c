/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:54 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 12:55:41 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_tile_skip(t_tiletype tile)
{
	if (tile == WALL || tile == '\0' || tile == BLANK)
	{
		printf("pass tile skip\n");
		return (0);
	}
	else
	{
		printf("fail tile skip\n");
		return (1);
	}
}

int	check_tile_floor(t_tiletype tile)
{
	if (tile == FLOOR || tile == NORTH || tile == SOUTH || tile == EAST
		|| tile == WEST)
	{
		printf("pass check tile floor\n");
		return (0);
	}
	else
	{
		printf("fail check tile floor\n");
		return (1);
	}
}

void	check_tile_player(t_game *game, t_tiletype tile)
{
	if (tile == NORTH || tile == SOUTH || tile == WEST || tile == EAST)
		game->mapdata.player_exists = 1;
}

int	check_adjacent_tile(t_tile **tilemap, int y, int x)
{
	if ((tilemap[y][x].up != NULL && tilemap[y][x].up->type != BLANK)
		&& (tilemap[y][x].down != NULL && tilemap[y][x].down->type != BLANK)
		&& (tilemap[y][x].left != NULL && tilemap[y][x].left->type != BLANK)
		&& (tilemap[y][x].right != NULL && tilemap[y][x].right->type != BLANK))
	{
		printf("pass adjacent tile floor\n");
		return (0);
	}
	else
	{
		printf("fail adjacent tile floor\n");
		printf("up: %d down: %d right: %d left: %d\n", tilemap[x][y].up->type, tilemap[x][y].down->type, tilemap[x][y].left->type, tilemap[x][y].right->type);
		return (1);
	}
}

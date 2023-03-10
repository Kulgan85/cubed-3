/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:55:30 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 15:17:01 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_other(t_game *game)
{
	game->doom_guy.height = 32;
	game->doom_guy.speed = 0.05;
	game->doom_guy.ismovef = 0;
	game->doom_guy.ismoveb = 0;
	game->doom_guy.isstrl = 0;
	game->doom_guy.isstrr = 0;
	game->doom_guy.isrotl = 0;
	game->doom_guy.isrotr = 0;
}

void	init_dir2(t_game *game, int y, int x)
{
	if (game->tilemap[y][x].type == SOUTH)
	{
		game->doom_guy.direction.x = 0;
		game->doom_guy.direction.y = 1;
		game->doom_guy.strafe.x = 1;
		game->doom_guy.strafe.y = 0;
	}
	if (game->tilemap[y][x].type == WEST)
	{
		game->doom_guy.direction.x = -1;
		game->doom_guy.direction.y = 0;
		game->doom_guy.strafe.x = 0;
		game->doom_guy.strafe.y = -1;
	}
}

void	init_dir(t_game *game, int y, int x)
{
	if (game->tilemap[y][x].type == NORTH)
	{
		game->doom_guy.direction.x = 0;
		game->doom_guy.direction.y = -1;
		game->doom_guy.strafe.x = -1;
		game->doom_guy.strafe.y = 0;
	}
	if (game->tilemap[y][x].type == EAST)
	{
		game->doom_guy.direction.x = 1;
		game->doom_guy.direction.y = 0;
		game->doom_guy.strafe.x = 0;
		game->doom_guy.strafe.y = -1;
	}
	init_dir2(game, y, x);
}

int	init_player(t_game *game)
{
	int	y;
	int	x;

	init_other(game);
	y = 0;
	while (y < game->mapdata.max_height)
	{
		x = 0;
		while (x < game->mapdata.max_width)
		{
			if (game->tilemap[y][x].type == NORTH
				|| game->tilemap[y][x].type == EAST
				|| game->tilemap[y][x].type == SOUTH
				|| game->tilemap[y][x].type == WEST)
			{
				game->doom_guy.x = x + 0.5;
				game->doom_guy.y = y + 0.5;
				init_dir(game, y, x);
				break ;
			}
			x++;
		}
		y++;
	}
	return (0);
}

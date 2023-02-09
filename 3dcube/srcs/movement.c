/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:37:53 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 15:14:44 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_loop(t_game *game)
{
	if (game->doom_guy.ismovef == 1)
		move_forward(game);
	if (game->doom_guy.ismoveb == 1)
		move_backward(game);
	if (game->doom_guy.isstrl == 1)
		strafe_left(game);
	if (game->doom_guy.isstrr == 1)
		strafe_right(game);
	if (game->doom_guy.isrotl == 1)
		rotate_left(game);
	if (game->doom_guy.isrotr == 1)
		rotate_right(game);
	return (0);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->doom_guy.x;
	new_y = game->doom_guy.y;
	new_x += (game->doom_guy.direction.x * game->doom_guy.speed);
	new_y += (game->doom_guy.direction.y * game->doom_guy.speed);
	if ((int)new_x != (int)game->doom_guy.x)
	{
		if (game->tilemap[(int)game->doom_guy.y][(int)new_x].type != WALL)
			game->doom_guy.x = new_x;
	}
	else
		game->doom_guy.x = new_x;
	if ((int)new_y != (int)game->doom_guy.y)
	{
		if (game->tilemap[(int)new_y][(int)game->doom_guy.x].type != WALL)
			game->doom_guy.y = new_y;
	}
	else
		game->doom_guy.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->doom_guy.x;
	new_y = game->doom_guy.y;
	new_x -= game->doom_guy.direction.x * game->doom_guy.speed;
	new_y -= game->doom_guy.direction.y * game->doom_guy.speed;
	if ((int)new_x != (int)game->doom_guy.x)
	{
		if (game->tilemap[(int)game->doom_guy.y][(int)new_x].type != WALL)
		game->doom_guy.x = new_x;
	}
	else
		game->doom_guy.x = new_x;
	if ((int)new_y != (int)game->doom_guy.y)
	{
		if (game->tilemap[(int)new_y][(int)game->doom_guy.x].type != WALL)
		game->doom_guy.y = new_y;
	}
	else
		game->doom_guy.y = new_y;
}

void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->doom_guy.x;
	new_y = game->doom_guy.y;
	new_x += game->doom_guy.strafe.x * game->doom_guy.speed;
	new_y += game->doom_guy.strafe.y * game->doom_guy.speed;
	if ((int)new_x != (int)game->doom_guy.x)
	{
		if (game->tilemap[(int)game->doom_guy.y][(int)new_x].type != WALL)
		game->doom_guy.x = new_x;
	}
	else
		game->doom_guy.x = new_x;
	if ((int)new_y != (int)game->doom_guy.y)
	{
		if (game->tilemap[(int)new_y][(int)game->doom_guy.x].type != WALL)
		game->doom_guy.y = new_y;
	}
	else
		game->doom_guy.y = new_y;
}

void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->doom_guy.x;
	new_y = game->doom_guy.y;
	new_x -= (game->doom_guy.strafe.x * game->doom_guy.speed);
	new_y -= (game->doom_guy.strafe.y * game->doom_guy.speed);
	if ((int)new_x != (int)game->doom_guy.x)
	{
		if (game->tilemap[(int)game->doom_guy.y][(int)new_x].type != WALL)
		game->doom_guy.x = new_x;
	}
	else
		game->doom_guy.x = new_x;
	if ((int)new_y != (int)game->doom_guy.y)
	{
		if (game->tilemap[(int)new_y][(int)game->doom_guy.x].type != WALL)
		game->doom_guy.y = new_y;
	}
	else
		game->doom_guy.y = new_y;
}

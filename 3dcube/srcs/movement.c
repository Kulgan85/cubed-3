/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:37:53 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/30 11:43:09 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	printf("Moving forward toward %f at a speed of %f\n",
		game->doom_guy.direction.x, game->doom_guy.speed);
	game->doom_guy.x += (game->doom_guy.direction.x * game->doom_guy.speed);
	game->doom_guy.y += (game->doom_guy.direction.y * game->doom_guy.speed);
}

void	move_backward(t_game *game)
{
	game->doom_guy.x -= game->doom_guy.direction.x * game->doom_guy.speed;
	game->doom_guy.y -= game->doom_guy.direction.y * game->doom_guy.speed;
}

void	strafe_left(t_game *game)
{
	t_pvector	strafedir;
	double		angle;

	angle = atan2(game->doom_guy.direction.x, game->doom_guy.direction.y)
		+ PI / 2;
	strafedir.x = cos(angle) * 1;
	strafedir.y = cos(angle) * 1;
	game->doom_guy.x += game->doom_guy.direction.x * game->doom_guy.speed
		+ strafedir.x * game->doom_guy.speed;
	game->doom_guy.y += game->doom_guy.direction.y * game->doom_guy.speed
		+ strafedir.y * game->doom_guy.speed;
}

void	strafe_right(t_game *game)
{
	t_pvector	strafedir;
	double		angle;

	angle = atan2(game->doom_guy.direction.x, game->doom_guy.direction.y)
		+ PI / 2;
	strafedir.x = cos(angle) * -1;
	strafedir.y = cos(angle) * -1;
	game->doom_guy.x += game->doom_guy.direction.x * game->doom_guy.speed
		+ strafedir.x * game->doom_guy.speed;
	game->doom_guy.y += game->doom_guy.direction.y * game->doom_guy.speed
		+ strafedir.y * game->doom_guy.speed;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:37:53 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/02 12:48:57 by tbertozz         ###   ########.fr       */
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
	game->doom_guy.x += game->doom_guy.strafe.x * game->doom_guy.speed;
	game->doom_guy.y += game->doom_guy.strafe.y * game->doom_guy.speed;
}

void	strafe_right(t_game *game)
{
	game->doom_guy.x -= (game->doom_guy.strafe.x * game->doom_guy.speed);
	game->doom_guy.y -= (game->doom_guy.strafe.y * game->doom_guy.speed);
}

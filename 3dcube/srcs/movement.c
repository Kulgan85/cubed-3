/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:37:53 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/03 13:43:41 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move_loop(t_game *game)
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

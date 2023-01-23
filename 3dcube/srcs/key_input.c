/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:42 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/23 14:01:30 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_input(int key, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	(void)game;
	if (key == KEY_ESC)
		printf("Esc Key\n");
	else if (key == KEY_UP)
		printf("Arrow Up Key\n");
	else if (key == KEY_DOWN)
		printf("Arrow Down Key\n");
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate_guy(key, game);
	else if (key == KEY_W || key == KEY_S || key == KEY_D || key == KEY_A)
		move_guy(key, game);
	return (0);
}

void	move_guy(int key, t_game *game)
{
	if (key == KEY_W)
		game->doom_guy.y -= 0.1;
	if (key == KEY_S)
		game->doom_guy.y += 0.1;
	if (key == KEY_A)
		game->doom_guy.x -= 0.1;
	if (key == KEY_D)
		game->doom_guy.x += 0.1;
	printf("Doomguy x: %f, Doomguy y: %f\n", game->doom_guy.x, game->doom_guy.y);
}

void	rotate_guy(int key, t_game *game)
{
	if (key == KEY_RIGHT)
		game->doom_guy.direction += 5;
	if (key == KEY_LEFT)
		game->doom_guy.direction -= 5;
	if (game->doom_guy.direction >= 360)
		game->doom_guy.direction -= 360;
	else if (game->doom_guy.direction < 0)
		game->doom_guy.direction += 360;
	printf("Doomguy angle: %f\n", game->doom_guy.direction);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:42 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/30 13:15:53 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_input(int key, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (key == KEY_ESC)
		close_win(game);
	else if (key == KEY_UP)
		move_guy(key, game);
	else if (key == KEY_DOWN)
		move_guy(key, game);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate_guy(key, game);
	else if (key == KEY_W || key == KEY_S || key == KEY_D || key == KEY_A)
		move_guy(key, game);
	printf("key pressed - %d\n", key);
	return (0);
}

void	move_guy(int key, t_game *game)
{
	if (key == KEY_W || key == KEY_UP)
		move_forward(game);
	if (key == KEY_S || key == KEY_DOWN)
		move_backward(game);
	if (key == KEY_A)
		strafe_left(game);
	if (key == KEY_D)
		strafe_right(game);
	printf("Doomguy x: %f, Doomguy y: %f\n", game->doom_guy.x, game->doom_guy.y);
}

t_pvector	do_rotate(t_pvector vector, double rotate)
{
	t_pvector	new;
	double		length;

	new.x = (vector.x * cos(rotate)) - (vector.y * sin(rotate));
	printf("x: %f\n", new.x);
	new.y = (vector.x * sin(rotate)) + (vector.y * cos(rotate));
	printf("y: %f\n", new.y);
	length = sqrt(new.x * new.x + new.y * new.y);
	printf("The length is: %f\n", length);
	if (length != 0)
	{
		new.x /= length;
		new.y /= length;
		return (new);
	}
	else
	{
		new.x = 0;
		new.y = 0;
		return (new);
	}
	printf("End of rotation\n");
}

void	rotate_guy(int key, t_game *game)
{
	if (key == KEY_RIGHT)
	{
		printf("doing rotate!\n");
		game->doom_guy.direction = do_rotate(game->doom_guy.direction,
				((PI / 8) * -1));
		printf("Doom_Guy was rotated!\n");
	}
	if (key == KEY_LEFT)
		game->doom_guy.direction = do_rotate(game->doom_guy.direction,
				PI / 8);
	printf("Doomguy angle: %f,%f\n", game->doom_guy.direction.x,
		game->doom_guy.direction.y);
}

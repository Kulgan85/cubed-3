/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:42 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/08 16:33:32 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_input(int key, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (key == KEY_UP || key == KEY_W)
		game->doom_guy.ismovef = 1;
	if (key == KEY_DOWN || key == KEY_S)
		game->doom_guy.ismoveb = 1;
	if (key == KEY_LEFT)
		game->doom_guy.isrotl = 1;
	if (key == KEY_RIGHT)
		game->doom_guy.isrotr = 1;
	if (key == KEY_A)
		game->doom_guy.isstrl = 1;
	if (key == KEY_D)
		game->doom_guy.isstrr = 1;
	printf("key pressed - %d\n", key);
	return (0);
}

int	key_release(int key, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (key == KEY_ESC)
		close_win(game);
	if (key == KEY_UP || key == KEY_W)
		game->doom_guy.ismovef = 0;
	if (key == KEY_DOWN || key == KEY_S)
		game->doom_guy.ismoveb = 0;
	if (key == KEY_LEFT)
		game->doom_guy.isrotl = 0;
	if (key == KEY_RIGHT)
		game->doom_guy.isrotr = 0;
	if (key == KEY_A)
		game->doom_guy.isstrl = 0;
	if (key == KEY_D)
		game->doom_guy.isstrr = 0;
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

void	rotate_right(t_game *game)
{
	printf("doing rotate!\n");
	game->doom_guy.direction = do_rotate(game->doom_guy.direction,
			((PI / 72)));
	printf("Doom_Guy was rotated!\n");
	game->doom_guy.strafe = do_rotate(game->doom_guy.strafe,
			((PI / 72)));
	printf("Strafe direction was rotated!\n");
	printf("Doomguy angle: %f, %f\n", game->doom_guy.direction.x,
		game->doom_guy.direction.y);
	printf("Strafe angle: %f, %f\n", game->doom_guy.strafe.x,
		game->doom_guy.strafe.y);
}

void	rotate_left(t_game *game)
{
	printf("doing rotate!\n");
	game->doom_guy.direction = do_rotate(game->doom_guy.direction, -(PI / 72));
	printf("Doom_Guy was rotated!\n");
	game->doom_guy.strafe = do_rotate(game->doom_guy.strafe, -(PI / 72));
	printf("Strafe direction was rotated!\n");
	printf("Doomguy angle: %f, %f\n", game->doom_guy.direction.x,
		game->doom_guy.direction.y);
	printf("Strafe angle: %f, %f\n", game->doom_guy.strafe.x,
		game->doom_guy.strafe.y);
}

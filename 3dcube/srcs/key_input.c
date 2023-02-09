/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:42 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 12:40:20 by tbertozz         ###   ########.fr       */
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
}

t_pvector	do_rotate(t_pvector vector, double rotate)
{
	t_pvector	new;
	double		length;

	new.x = (vector.x * cos(rotate)) - (vector.y * sin(rotate));
	new.y = (vector.x * sin(rotate)) + (vector.y * cos(rotate));
	length = sqrt(new.x * new.x + new.y * new.y);
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
}

void	rotate_right(t_game *game)
{
	game->doom_guy.direction = do_rotate(game->doom_guy.direction,
			((PI / 72)));
	game->doom_guy.strafe = do_rotate(game->doom_guy.strafe,
			((PI / 72)));
}

void	rotate_left(t_game *game)
{
	game->doom_guy.direction = do_rotate(game->doom_guy.direction, -(PI / 72));
	game->doom_guy.strafe = do_rotate(game->doom_guy.strafe, -(PI / 72));
}

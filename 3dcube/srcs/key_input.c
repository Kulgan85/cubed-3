/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:42 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 15:20:27 by jwilliam         ###   ########.fr       */
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

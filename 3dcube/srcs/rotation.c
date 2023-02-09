/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:19:24 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 15:26:44 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

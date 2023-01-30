/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:42 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/30 10:27:42 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_input(int key, void *param)
{
	t_game		*game;

	game = (t_game *)param;
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
	printf("key pressed - %d\n", key);
	return (0);
}

void	move_forward(t_game *game)
{
	printf("Moving forward toward %f at a speed of %f\n", game->doom_guy.direction.x, game->doom_guy.speed);
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

void	move_guy(int key, t_game *game)
{
	if (key == KEY_W)
		move_forward(game);
	if (key == KEY_S)
		move_backward(game);
	if (key == KEY_A)
		strafe_left(game);
	if (key == KEY_D)
		strafe_right(game);
	printf("Doomguy x: %f, Doomguy y: %f\n", game->doom_guy.x, game->doom_guy.y);
}

t_pvector	do_rotate(t_pvector vector, double rotate, char *direction)
{
	t_pvector	new;
	double		length;

	if (ft_strncmp(direction, "right", 6) == 0)
	{
		new.x = (vector.x * cos(rotate)) + (vector.y * sin(rotate));
		printf("x: %f\n", new.x);
		new.y = (vector.x * cos(rotate)) - (vector.y * sin(rotate));
		printf("y: %f\n", new.y);
	}
	else if (ft_strncmp(direction, "left", 5) == 0)
	{
		new.x = (vector.x * cos(rotate)) - (vector.y * sin(rotate));
		printf("x: %f\n", new.x);
		new.y = (vector.x * cos(rotate)) + (vector.y * sin(rotate));
		printf("y: %f\n", new.y);
	}
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
				((PI * -1) / 8), "right");
		printf("Doom_Guy was rotated!\n");
	}
	if (key == KEY_LEFT)
		game->doom_guy.direction = do_rotate(game->doom_guy.direction,
				PI / 8, "left");
	printf("Doomguy angle: %f,%f\n", game->doom_guy.direction.x,
		game->doom_guy.direction.y);
}

/*
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
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:41:42 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/12 20:45:26 by jwilliam         ###   ########.fr       */
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
	else if (key == KEY_LEFT)
		printf("Arrow Left Key\n");
	else if (key == KEY_RIGHT)
		printf("Arrow Right Key\n");
	return (0);
}

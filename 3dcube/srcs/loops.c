/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:00:25 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/10 12:45:04 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_game *game)
{
	move_loop(game);
	draw_bg(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->img.pointer, 0, 0);
	return (0);
}

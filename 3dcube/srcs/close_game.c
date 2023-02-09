/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:03:31 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 15:12:36 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_window);
	free_2d_array(game->file);
	free_tilemap(game);
	exit(0);
}

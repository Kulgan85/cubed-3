/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:03:31 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/10 10:50:58 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_window);
	free(game->mlx);
	free(game->img);
	free_tilemap(game);
	free_map(game);
	free_textures(game);
	exit(0);
}

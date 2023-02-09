/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:03:31 by jwilliam          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/09 14:40:01 by tbertozz         ###   ########.fr       */
=======
/*   Updated: 2023/02/09 15:01:23 by jwilliam         ###   ########.fr       */
>>>>>>> 45d907f28ad2d2bc1bd61e59be94fd31ce2d2f1f
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_window);
<<<<<<< HEAD
	free(game->mlx);
	free(game->img);
	free_tilemap(game->tilemap);
=======
	free_2d_array(game->file);
	free_tilemap(game);
>>>>>>> 45d907f28ad2d2bc1bd61e59be94fd31ce2d2f1f
	exit(0);
}

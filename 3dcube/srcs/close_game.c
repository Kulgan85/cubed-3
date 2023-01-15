/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:03:31 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/15 16:53:52 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_game game)
{
	mlx_destroy_window(game.mlx, game.mlx_window);
	free(game.mlx);
	free(game.img);
//	free_2d_array(game->tilemap);
	exit(0);
}

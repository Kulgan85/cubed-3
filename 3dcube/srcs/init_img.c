/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:47:42 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/10 13:17:29 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_image(t_game *game)
{
	game->img.width = WIN_WIDTH;
	game->img.height = WIN_HEIGHT;
	game->img.pointer = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.address = mlx_get_data_addr(game->img.pointer,
			&game->img.bpp, &game->img.l_size, &game->img.endian);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:03:02 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 12:46:22 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	imageload(t_game *game)
{
	int	height;
	int	width;

	game->mapdata.northimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.no, &width, &height);
	if (!game->mapdata.northimg)
		print_error(4, "North wall image not set");
	game->mapdata.southimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.so, &width, &height);
	if (!game->mapdata.southimg)
		print_error(4, "South wall image not set");
	game->mapdata.eastimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.ea, &width, &height);
	if (!game->mapdata.eastimg)
		print_error(4, "East wall image not set");
	game->mapdata.westimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.we, &width, &height);
	if (!game->mapdata.westimg)
		print_error(4, "West wall image not set");
	if (!game->mapdata.northimg || !game->mapdata.southimg
		|| !game->mapdata.eastimg || !game->mapdata.westimg)
		print_error(4, "images not loaded\n");
	return ;
}

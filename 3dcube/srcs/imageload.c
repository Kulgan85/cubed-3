/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:03:02 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/06 16:08:54 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// init_textures(t_game *game, t_images *images)
// {
	
// }

void	imageload(t_game *game)
{
	int	height;
	int	width;

	printf("hacking images\n");
	game->mapdata.northimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.no, &width, &height);
	printf("good\n");
	if (!game->mapdata.northimg)
		printf("NORTH BAD: %s\n", game->mapdata.no);
	printf("still good\n");
	game->mapdata.southimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.so, &width, &height);
	printf("really good still\n");
	if (!game->mapdata.southimg)
		printf("SOUTH BAD: %s\n", game->mapdata.so);
	game->mapdata.eastimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.ea, &width, &height);
	printf("good is just a concept\n");
	if (!game->mapdata.eastimg)
		printf("TEAPOT ERROR: %s\n", game->mapdata.ea);
	printf("good is good\n");
	game->mapdata.westimg = mlx_xpm_file_to_image(game->mlx,
			game->mapdata.we, &width, &height);
	printf("good cannot be tamed\n");
	if (!game->mapdata.westimg)
		printf("ERROR 507: %s\n", game->mapdata.we);
	printf("ARE YOU NOT GOOD YET?\n");
	if (!game->mapdata.northimg || !game->mapdata.southimg
		|| !game->mapdata.eastimg || !game->mapdata.westimg)
			print_error(8, "images not load\n");
	printf("we're in\n");
	return ;
}

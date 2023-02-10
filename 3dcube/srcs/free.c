/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:17:41 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/10 12:08:15 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_tilemap(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->mapdata.max_height)
	{
		free(game->tilemap[i]);
		i++;
	}
	free(game->tilemap);
	game->tilemap = NULL;
}

void	free_map(t_game *game)
{
	free_2d_array(game->file);
}

void	free_textures(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img->pointer);
}

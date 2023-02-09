/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:44:49 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/09 15:46:14 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_images *image, int x, int y, int colour)
{
	int	index;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		index = (x * image->bpp / 8) + (y * image->l_size);
		image->address[index] = colour;
		image->address[++index] = colour >> 8;
		image->address[++index] = colour >> 16;
	}
}

void	*texture_picker(t_game *game, t_ray *ray_stuff)
{
	void	*texture;

	texture = NULL;
	if (ray_stuff->side == 0)
	{
		if (ray_stuff->ray_dir_x < 0)
			texture = game->mapdata.eastimg;
		else
			texture = game->mapdata.westimg;
	}
	else if (ray_stuff->side == 1)
	{
		if (ray_stuff->ray_dir_y < 0)
			texture = game->mapdata.northimg;
		else
			texture = game->mapdata.southimg;
	}
	return (texture);
}

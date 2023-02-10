/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_beegee.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:09 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/10 12:44:21 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_bg(t_game *game)
{
	int		*new_image;
	int		i;

	ft_bzero(game->img.address, WIN_WIDTH * WIN_HEIGHT * (game->img.bpp / 8));
	new_image = (int *)(game->img.address);
	i = 0;
	while (i < (WIN_WIDTH * (WIN_HEIGHT / 2)))
	{
		new_image[i] = create_rgb(game->mapdata.c[0], game->mapdata.c[1],
				game->mapdata.c[2]);
		i++;
	}
	while (i < (WIN_WIDTH * (WIN_HEIGHT)))
	{
		new_image[i] = create_rgb(game->mapdata.f[0], game->mapdata.f[1],
				game->mapdata.f[2]);
		i++;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

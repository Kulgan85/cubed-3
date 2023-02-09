/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:57:52 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 15:58:54 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	savelines(t_game *game, int x, int y, t_tile **tilemap)
{
	while (x <= game->mapdata.max_width)
	{
		tilemap[y][x].type = BLANK;
		x++;
	}
	return (x);
}

void	incrementator(t_game *game, t_number num, t_tile **tilemap, int skip)
{
	while (num.x < game->mapdata.max_width)
	{
		if (game->file[skip + num.y][num.x] == '\0'
			|| game->file[skip + num.y][num.x] == EOF)
			num.x = savelines(game, num.x, num.y, tilemap);
		else
		{
			tilemap[num.y][num.x].type = define_tiletype(game->file[skip
					+ num.y][num.x]);
			setup_tile(tilemap, num.y, num.x, game);
			num.x++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:20:04 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/12 10:27:49 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

floodfill_check(t_game game)
{
    while (game.tilemap[x][y] != "\n")
    {
        if (game.tilemap[x][y] == "0")
        {
            if (game.tilemap[x-1][y] == " " || game.tilemap[x][y-1] == " "
                || game.tilemap[x+1][y] == " " || game.tilemap[x][y+1] == " ")
            {
                printf("Flood fill failure");
            }
        }
    }
}
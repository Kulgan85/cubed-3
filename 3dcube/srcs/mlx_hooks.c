/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:00:52 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/16 12:44:13 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_mlx_hooks(t_game game)
{
	mlx_hook(game.mlx_window, 2, 0, key_input, &game);
	mlx_hook(game.mlx_window, 17, 0, close_win, &game);
	return ;
}

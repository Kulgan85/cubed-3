/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:00:52 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/12 20:41:14 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_mlx_hooks(t_game game)
{
	mlx_hook(game.mlx_window, 2, 0, key_input, &game);
	mlx_hook(game.mlx_window, 17, 0 , close_win, &game);
	return ;
}
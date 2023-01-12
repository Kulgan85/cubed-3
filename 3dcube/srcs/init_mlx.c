/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:09:43 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/12 19:51:07 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_mlx(t_game game)
{
	void	*mlx;
	void	*mlx_win;

	game.mlx = mlx_init();
	game.mlx_window = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
}

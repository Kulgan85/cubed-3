/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:34:33 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/10 12:43:48 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	start_mlx(&game);
	if (argc != 2)
		print_error(1, "Invalid arguments - ./cub3d path_to_mapfile/*.cub");
	if (ft_strncmp(".cub", &argv[1][(int)(ft_strlen(argv[1])) - 4], 4) != 0)
		print_error(1, "Invalid map type. Please use .cub");
	if (read_map(argv[1], &game) != 0)
		print_error(1, "Map cannot be read");
	if (init_check(&game) != 0)
		print_error(1, "Invalid map file");
	imageload(&game);
	game.tilemap = generate_tilemap(&game);
	init_player(&game);
	init_image(&game);
	draw_bg(&game);
	raycast(&game);
	mlx_put_image_to_window(game.mlx, game.mlx_window, game.img.pointer, 0, 0);
	set_mlx_hooks(&game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}

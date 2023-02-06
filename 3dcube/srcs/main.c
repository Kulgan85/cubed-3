/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:34:33 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/06 16:31:07 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	start_mlx(&game);
	if (argc != 2)
		print_error(1, "Invalid arguments - ./cub3d path_to_file/*.cub");
	if (read_map(argv[1], &game) != 0)
		printf("FUCKED");
	printf("map read\n");
	if (init_check(&game) != 0)
		print_error(1, "Invalid map file");
	imageload(&game);
	printf("generating tilemap\n");
	game.tilemap = generate_tilemap(&game);
	printf("generating tilemap done\n");
	init_player(&game);
	printf("init player done\n");
	init_image(&game);
	printf("init player done\n");
	draw_bg(&game);
	printf("pre raycast\n");
	raycast(&game);
	printf("post raycast\n");
	mlx_put_image_to_window(game.mlx, game.mlx_window, game.img->pointer, 0, 0);
	printf("BG good\n");
	set_mlx_hooks(&game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}

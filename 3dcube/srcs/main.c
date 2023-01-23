/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:34:33 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/23 16:23:06 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_color	color;

	start_mlx(&game);
	if (argc != 2)
		print_error(1, "Invalid arguments - ./cub3d path_to_file/*.cub");
	printf("init check\n");
	if (read_map(argv[1], &game) != 0)
		printf("FUCKED");
	printf("map read\n");
	if (init_check(&game) != 0)
		print_error(1, "Invalid map file");
	printf("init done\n");
	printf("try generate tile map\n");
	game.tilemap = generate_tilemap(&game);
	init_player(&game);
	//game.img = init_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	color.b = 100;
	color.g = 100;
	color.r = 100;
	color.a = 255;
	printf("test\n");
	game.img = new_panel(&game, color);
	printf("good panel\n");
	mlx_put_image_to_window(game.mlx, game.mlx_window, game.img, 0, 0);
	printf("bad mlx\n");
	draw_bg(&game);
	set_mlx_hooks(game);
	mlx_loop(game.mlx);
}

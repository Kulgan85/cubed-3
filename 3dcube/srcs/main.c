/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:34:33 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/18 20:25:00 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		print_error(1, "Invalid arguments - ./cub3d path_to_file/*.cub");
	printf("init check\n");
	if (read_map(argv[1], &game) != 0)
		printf("FUCKED");
	printf("map read\n");
	for (int i = 0; game.file[i] != 0; i++)
		printf("%s", game.file[i]);
	if (init_check(&game) != 0)
		print_error(1, "Invalid map file");
	printf("init done\n");
	printf("try generate tile map\n");
	game.tilemap = generate_tilemap(game.file, &game);
	// if (map_init_check(&game, argv[1]) != 0)
	// 	print_error(1, "The maps fucked");
//	start_mlx(&game);
//	init_image();
//	set_mlx_hooks(game);
//	mlx_loop(game.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:34:33 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/16 14:57:43 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	i = 0;
	if (argc != 2)
		print_error(1, "Invalid arguments - ./cub3d path_to_file/*.cub");
	printf("init check\n");
	if (read_map(argv[1], &game) != 0)
		printf("FUCKED");
	while (game.file[i])
	{
		printf("%s", game.file[i]);
		i++;
	}
	if (init_check(&game) != 0)
		print_error(1, "Invalid map file");
	printf("init done\n");
	// if (map_init_check(&game, argv[1]) != 0)
	// 	print_error(1, "The maps fucked");
//	start_mlx(&game);
//	init_image();
//	set_mlx_hooks(game);
//	mlx_loop(game.mlx);
}

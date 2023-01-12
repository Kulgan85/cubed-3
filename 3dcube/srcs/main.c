/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:34:33 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/12 14:41:51 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		file;

	if (argc != 2)
		print_error(1, "Invalid arguments - ./cub3d path_to_file/*.cub");
	file = open(argv[1], O_RDONLY);
	if (file < 0)
		print_error(1, "Unable to open map file");
	if (read_map(file) != 1)
		print_error(1, "Invalid map file");
	start_mlx();
	init_image();
	set_mlx_hooks();
	mlx_loop(mlx);
}

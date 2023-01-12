/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:34:33 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/12 12:41:54 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		file;

	if (argc != 2)
		printf("Invalid Arguments - ./cub3d <path_to_map/*.cub>\n");
	else
	{
		file = open(argv[1], O_RDONLY);
		if (file < 0)
			error_unable_to_open_file();
		if (read_map(file) != 1)
			error_bad_map();
		init_image();
		set_mlx_hooks();
		loop_mlx_inst();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:20:04 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 16:12:39 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Returns the tiletype that corresponds to <definer> */
t_tiletype	define_tiletype(char definer)
{
	if (definer == '1')
		return (WALL);
	else if (definer == '0')
		return (FLOOR);
	else if (definer == 'N')
		return (NORTH);
	else if (definer == 'E')
		return (EAST);
	else if (definer == 'W')
		return (WEST);
	else if (definer == 'S')
		return (SOUTH);
	return (BLANK);
}

/* Set the size, original type and neighboors of the <x><y> tile of <tilemap> */
void	setup_tile(t_tile **tilemap, int y, int x, t_game *game)
{
	tilemap[y][x].og_type = tilemap[y][x].type;
	tilemap[y][x].position.x = x;
	tilemap[y][x].position.y = y;
	if (y > 0)
		tilemap[y][x].up = &tilemap[y - 1][x];
	else
		tilemap[y][x].up = NULL;
	if (y < game->mapdata.max_height)
		tilemap[y][x].down = &tilemap[y + 1][x];
	else
		tilemap[y][x].down = NULL;
	if (x > 0)
		tilemap[y][x].left = &tilemap[y][x - 1];
	else
		tilemap[y][x].left = NULL;
	if (x < game->mapdata.max_width)
		tilemap[y][x].right = &tilemap[y][x + 1];
	else
		tilemap[y][x].right = NULL;
}

t_tile	**alloc_tilemap(int skip, t_game *game)
{
	int		i;
	t_tile	**new;

	i = 0;
	new = (t_tile **)malloc(sizeof(t_tile *) * game->mapdata.max_height + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (game->file[skip + i] != NULL)
	{
		new[i] = (t_tile *)malloc(sizeof(t_tile) * game->mapdata.max_width + 1);
		if (new == NULL)
		{
			print_error(2, "malloc error");
			while (i > 0)
				free(new[i--]);
			return (NULL);
		}
		i++;
	}
	return (new);
}

int	generate_tilemap_init(t_game *game)
{
	int	skip;

	skip = skip_lines(game);
	game->mapdata.max_height = (count_height(game, skip));
	game->mapdata.max_width = (count_width(game, skip) - 1);
	return (skip);
}

/* Returns a t_tile table filled according to map,
columns ends in a NULL pointer */
t_tile	**generate_tilemap(t_game *game)
{
	t_tile		**tilemap;
	t_number	num;
	int			skip;

	skip = generate_tilemap_init(game);
	tilemap = alloc_tilemap(skip, game);
	if (!tilemap)
		print_error(2, "malloc error");
	num.y = 0;
	while (game->file[skip + num.y] && num.y < game->mapdata.max_height)
	{
		num.x = 0;
		incrementator(game, num, tilemap, skip);
		num.y++;
	}
	if (perform_floodfill(game, tilemap) != 1)
		print_error(3, "Invalid floodfill");
	return (tilemap);
}

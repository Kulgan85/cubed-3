/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:44:22 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/12 15:55:36 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	iswhitespace(int i, char *mapfile)
{
	if (mapfile[i] == "\n" || mapfile[i] == " " || mapfile[i] == "\t")
		i++;
	return (i);
}

initialise_struct(t_mapdata mapdata)
{
	mapdata.no == NULL;
	mapdata.so == NULL;
	mapdata.ea == NULL;
	mapdata.we == NULL;
	mapdata.c[0] == -1;
	mapdata.f[0] == -1;
}

charcheck(int i, t_game game, char *file)
{
	if (!ft_strncmp("NO ", &file[i], 3) == 0)
		i = add_texture(i, file);
	else if (!ft_strncmp("SO ", &file[i], 3) == 0)
		i = add_texture(i, file);
	else if (!ft_strncmp("EA ", &file[i], 3) == 0)
		i = add_texture(i, file);
	else if (!ft_strncmp("WE ", &file[i], 3) == 0)
		i = add_texture(i, file);
	else if (!ft_strncmp("C ", &file[i], 2) == 0)
		i = add_texture(i, file);
	else if (!ft_strncmp("F ", &file[i], 2) == 0)
		i = add_texture(i, file);
	else
		i = -1;
	return (i);
}

int	init_check(char *mapfile, t_game game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	initialise_struct(*game.mapdata);
	while (j < 6)
	{
		iswhitespace(i, mapfile);
		charcheck(i, game, mapfile);
		if (i < 0)
			return (error("BAD_MAP"));
		i++;
		j++;
	}
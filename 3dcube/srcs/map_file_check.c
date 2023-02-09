/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:44:22 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/09 14:11:59 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialise_struct(t_mapdata *mapdata)
{
	int		i;

	mapdata->no = NULL;
	mapdata->so = NULL;
	mapdata->ea = NULL;
	mapdata->we = NULL;
	i = 0;
	while (i <= 2)
	{
		mapdata->c[i] = -1;
		mapdata->f[i] = -1;
		i++;
	}
	mapdata->max_height = 0;
	mapdata->max_width = 0;
	mapdata->player_exists = 0;
}

int	charcheck(int i, t_game *game, char *file)
{
	char	**temp;

	if (!file)
		return (-1);
	temp = ft_split(file, ' ');
	if (!temp)
		return (-1);
	if (ft_strncmp("NO", temp[0], 3) == 0)
		i = add_texture(i + 3, temp[1], game, 0);
	else if (ft_strncmp("SO", temp[0], 3) == 0)
		i = add_texture(i + 3, temp[1], game, 1);
	else if (ft_strncmp("EA", temp[0], 3) == 0)
		i = add_texture(i + 3, temp[1], game, 2);
	else if (ft_strncmp("WE", temp[0], 3) == 0)
		i = add_texture(i + 3, temp[1], game, 3);
	else if (ft_strncmp("C", temp[0], 2) == 0)
		i = set_colors(i, temp[1], game, 0);
	else if (ft_strncmp("F", temp[0], 2) == 0)
		i = set_colors(i, temp[1], game, 1);
	else
		i = -1;
	free (temp);
	return (i);
}

int	check_map_settings(t_game *game)
{
	int		i;

	i = 0;
	if (game->mapdata.no == NULL)
		return (-1);
	if (game->mapdata.so == NULL)
		return (-1);
	if (game->mapdata.ea == NULL)
		return (-1);
	if (game->mapdata.we == NULL)
		return (-1);
	while (i < 3)
	{
		if (game->mapdata.c[i] < 0 || game->mapdata.c[i] > 255)
		{
			printf("Error - C[%i] was bad. It was %i\n", i, game->mapdata.c[i]);
			return (-1);
		}
		if (game->mapdata.f[i] < 0 || game->mapdata.f[i] > 255)
			return (-1);
		i++;
	}
	return (0);
}

int	init_check(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	initialise_struct(&game->mapdata);
	printf("before char check\n");
	while (game->file[j] != NULL)
	{
		printf("in charcheck\n");
		charcheck(i, game, game->file[j]);
		j++;
	}
	printf("post charcheck\n");
	return (check_map_settings(game));
}

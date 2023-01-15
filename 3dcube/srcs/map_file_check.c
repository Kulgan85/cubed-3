/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:44:22 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/15 17:49:15 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_texture(int i, char *file, t_game *game, int id)
{
	int		j;
	char	*temp;

	j = 0;
	while (file[j] != '\n')
		j++;
	temp = (char *)malloc(sizeof(char) * j + 1);
	ft_memcpy(temp, file, j);
	temp[j + 1] = '\0';
	if (id == 0)
		game->mapdata.no = ft_strdup(temp);
	else if (id == 1)
		game->mapdata.so = ft_strdup(temp);
	else if (id == 2)
		game->mapdata.ea = ft_strdup(temp);
	else if (id == 3)
		game->mapdata.we = ft_strdup(temp);
	free (temp);
	return (i + j);
}

int	set_colors(int i, char *file, t_game *game, int id)
{
	int		j;
	int		k;
	char	**temp;

	j = 0;
	k = 0;
	while (file[j] != '\n')
		j++;
	temp = ft_split(file, ',');
	if (id == 0)
	{
		while (k++ <= 2)
			game->mapdata.c[k] = ft_atoi(temp[k]);
	}
	else if (id == 1)
	{
		while (k++ <= 2)
			game->mapdata.f[k] = ft_atoi(temp[k]);
	}
	free_2d_array(temp);
	return (i + j);
}

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
}

int	charcheck(int i, t_game *game, char *file)
{
	if (ft_strncmp("NO ", &file[i], 3) == 0)
		i = add_texture(i + 3, file, game, 0);
	else if (ft_strncmp("SO ", &file[i], 3) == 0)
		i = add_texture(i + 3, file, game, 1);
	else if (ft_strncmp("EA ", &file[i], 3) == 0)
		i = add_texture(i + 3, file, game, 2);
	else if (ft_strncmp("WE ", &file[i], 3) == 0)
		i = add_texture(i + 3, file, game, 3);
	else if (ft_strncmp("C ", &file[i], 2) == 0)
		i = set_colors(i + 2, file, game, 0);
	else if (ft_strncmp("F ", &file[i], 2) == 0)
		i = set_colors(i + 2, file, game, 1);
	else
		i = -1;
	return (i);
}

int	init_check(char *mapfile, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	initialise_struct(&game->mapdata);
	while (j < 6)
	{
		iswhitespace(i, mapfile);
		charcheck(i, game, mapfile);
		if (i < 0)
			return (-1);
		i++;
		j++;
	}
	return (0);
}

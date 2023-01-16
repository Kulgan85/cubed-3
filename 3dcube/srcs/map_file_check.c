/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:44:22 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/16 16:16:33 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_texture(int i, char *file, t_game *game, int id)
{
	int		j;
	char	*temp;

	printf("within Add Texture\n");
	j = 0;
	while (file[j] != '\n')
		j++;
	temp = (char *)malloc(sizeof(char) * j + 1);
	if (!temp)
		return (-1);
	ft_memcpy(temp, file, j);
	temp[j] = '\0';
	printf("%s\n", temp);
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

	printf("set colors %s\n", file);
	j = 0;
	k = 0;
	while (file[j] != '\n')
		j++;
	temp = ft_split(file, ',');
	while (k < 3)
	{
		if (id == 0)
			game->mapdata.c[k] = ft_atoi(temp[k]);
		else if (id == 1)
			game->mapdata.f[k] = ft_atoi(temp[k]);
		k++;
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
	char	**temp;

	temp = ft_split(file, ' ');
	printf("In charcheck\n");
	printf("%s\n", file);
	if (ft_strncmp("NO", temp[0], 2) == 0)
		i = add_texture(i + 3, temp[1], game, 0);
	else if (ft_strncmp("SO", temp[0], 2) == 0)
		i = add_texture(i + 3, temp[1], game, 1);
	else if (ft_strncmp("EA", temp[0], 2) == 0)
		i = add_texture(i + 3, temp[1], game, 2);
	else if (ft_strncmp("WE", temp[0], 2) == 0)
		i = add_texture(i + 3, temp[1], game, 3);
	else if (ft_strncmp("C", temp[0], 1) == 0)
		i = set_colors(i, temp[1], game, 0);
	else if (ft_strncmp("F", temp[0], 1) == 0)
		i = set_colors(i, temp[1], game, 1);
	else
		i = -1;
	free (temp);
	return (i);
}

int	init_check(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	initialise_struct(&game->mapdata);
	while (game->file[j])
	{
		charcheck(i, game, game->file[j]);
		printf("no is: %s\n", game->mapdata.no);
		printf("ea is: %s\n", game->mapdata.ea);
		printf("so is: %s\n", game->mapdata.so);
		printf("we is: %s\n", game->mapdata.we);
		printf("c is: %d%d%d\n", game->mapdata.c[0], game->mapdata.c[1], game->mapdata.c[2]);
		printf("f is: %d%d%d\n", game->mapdata.f[0], game->mapdata.f[1], game->mapdata.f[2]);
		if (i < 0)
			return (-1);
		i++;
		j++;
	}
	return (0);
}

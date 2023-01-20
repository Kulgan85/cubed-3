/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:44:22 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/20 11:21:36 by tbertozz         ###   ########.fr       */
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
	if (id == 0 && game->mapdata.no == NULL)
		game->mapdata.no = ft_strdup(temp);
	else if (id == 1 && game->mapdata.so == NULL)
		game->mapdata.so = ft_strdup(temp);
	else if (id == 2 && game->mapdata.ea == NULL)
		game->mapdata.ea = ft_strdup(temp);
	else if (id == 3 && game->mapdata.we == NULL)
		game->mapdata.we = ft_strdup(temp);
	else
		print_error(3, "Duplicate texture files");
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
		if (id == 0 && game->mapdata.c[k] == -1)
			game->mapdata.c[k] = ft_atoi(temp[k]);
		else if (id == 1 && game->mapdata.f[k] == -1)
			game->mapdata.f[k] = ft_atoi(temp[k]);
		else
			print_error(3, "Duplicate texture files");
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
	mapdata->max_height = 0;
	mapdata->max_width = 0;
}

int	charcheck(int i, t_game *game, char *file)
{
	char	**temp;

	if (!file)
		return (-1);
	temp = ft_split(file, ' ');
	if (!temp)
		return (-1);
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
			return (-1);
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
	printf("start check map\n");
	while (game->file[j] != NULL)
	{
		printf("current file line - %s\n", game->file[j]);
		charcheck(i, game, game->file[j]);
		printf("no is: %s\n", game->mapdata.no);
		printf("ea is: %s\n", game->mapdata.ea);
		printf("so is: %s\n", game->mapdata.so);
		printf("we is: %s\n", game->mapdata.we);
		printf("c is: %d,%d,%d\n", game->mapdata.c[0], game->mapdata.c[1], game->mapdata.c[2]);
		printf("f is: %d,%d,%d\n", game->mapdata.f[0], game->mapdata.f[1], game->mapdata.f[2]);
		j++;
	}
	return(check_map_settings(game));
}

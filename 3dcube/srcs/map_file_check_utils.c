/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:44:32 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/20 12:47:08 by tbertozz         ###   ########.fr       */
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

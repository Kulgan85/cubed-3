/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:38:25 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/20 11:31:32 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	iswhitespace(int i, char *mapfile)
{
	if (mapfile[i] == '\n' || mapfile[i] == 32 || mapfile[i] == '\t')
		i++;
	return (i);
}

int	skip_lines(t_game *game)
{
	int			i;

	i = 0;
	while (ft_strtrim(game->file[i], " ")[0] != '1' &&
			ft_strtrim(game->file[i], " ")[0] != '0')
		i++;
	return (i);
}

int	count_height(t_game *game, int skip)
{
	int		i;

	i = 0;
	while (game->file[skip + i] != 0)
		i++;
	return (i);
}

int	count_width(t_game *game, int skip)
{
	int		max;
	int		i;
	int		j;

	max = 0;
	i = 0;
	j = 0;
	while (game->file[skip + i] != 0)
	{
		j = ft_strlen(game->file[skip + i]);
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}
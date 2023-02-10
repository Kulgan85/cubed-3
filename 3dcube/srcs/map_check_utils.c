/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:38:25 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/10 13:17:19 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	iswhitespace(int i, char *mapfile)
{
	if (mapfile[i] == '\n' || mapfile[i] == 32 || mapfile[i] == '\t')
		i++;
	return (i);
}

int	skip_lines(t_game *game)
{
	int			i;
	char		*temp;

	i = 0;
	temp = ft_strtrim(game->file[i], " ");
	while (temp[i] != '1' && temp[i] != '0')
	{
		free(temp);
		temp = ft_strtrim(game->file[i], " ");
		i++;
	}
	free(temp);
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

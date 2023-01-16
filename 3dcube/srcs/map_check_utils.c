/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:38:25 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/16 15:45:41 by tbertozz         ###   ########.fr       */
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

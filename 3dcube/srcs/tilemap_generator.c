/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:26:44 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/16 14:51:11 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Return the number of '\n' in the map file */
/* This is the number of rows in the map (Y value)*/
static int	file_linecount(char	*file)
{
	int		linecount;
	int		fd;
	char	*readcount;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	linecount = 1;
	while (1)
	{
		readcount = get_next_line(fd);
		if (readcount == NULL)
			break ;
		else
			linecount++;
		free (readcount);
	}
	close (fd);
	return (linecount);
}

/* Allocation of memory for a string array with the same */
/* lines as the map file */
/* This is the number of columns in the map (X value)*/
static char	**alloc_collumns(char *file)
{
	char	**map;
	int		line_count;

	line_count = file_linecount(file);
	if (line_count <= 0)
		printf("open or reading error, check the file exists");
	map = malloc(sizeof(char *) * line_count + 1);
	if (map == NULL)
		printf("malloc error on alloc_map");
	return (map);
}

/* Creates the 2D char map found in the map file */
int	**read_map(char *file, t_game *game)
{
	char	**map;
	char	*temp;
	int		fd;
	int		i;

	map = alloc_collumns(file);
	if (map == NULL)
	{
		printf("NULL MAP");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	i = 0;
	while (map[i])
	{	
		temp = get_next_line(fd);
		if (!temp)
			break ;
		map[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	map[i] = NULL;
	close (fd);
	game->file = map;
	return (0);
}

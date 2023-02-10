/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:26:44 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/10 11:41:50 by tbertozz         ###   ########.fr       */
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
	linecount = 0;
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
		print_error(3, "Open or reading error, check the file exists\n");
	map = malloc(sizeof(char *) * line_count + 1);
	if (map == NULL)
		print_error(2, "Malloc error");
	return (map);
}

/* Creates the 2D char map found in the map file */
int	read_map(char *file, t_game *game)
{
	char	**map;
	char	*temp;
	int		fd;
	int		i;
	int		linecount;

	map = alloc_collumns(file);
	if (!map)
		print_error(2, "Malloc error");
	linecount = file_linecount(file);
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < linecount)
	{	
		temp = get_next_line(fd);
		if (!temp)
			break ;
		map[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	map[i] = 0;
	close (fd);
	game->file = map;
	return (0);
}

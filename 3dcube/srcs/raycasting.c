/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:42:08 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/30 17:04:44 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_images *image, int x, int y, int colour)
{
	int	index;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		index = (x * image->bpp / 8) + (y * image->l_size);
		image->address[index] = colour;
		image->address[++index] = colour >> 8;
		image->address[++index] = colour >> 16;
	}
}

t_rayhit	cast_ray(t_game *game, double ray_dir_x, double ray_dir_y, t_rayhit *ray_hit)
{
	int			length;
	int			cell_x;
	int			cell_y;
	int			i;

	printf("cast ray\n");
	i = 0;
	length = game->mapdata.max_width * game->mapdata.max_height;
	ray_hit->wall_distance = 0;
	ray_hit->wall_normal = 0;
	ray_hit->wall_texture = NULL;
	ray_hit->wall_colour = create_rgb(255, 0, 0);
	printf("length = %i\n", length);
	while (i < length)
	{
		cell_x = (int)(game->doom_guy.x + ray_dir_x * i);
		cell_y = (int)(game->doom_guy.y + ray_dir_y * i);
		printf("cell x: %i\n cell y: %i\n", cell_x, cell_y);
		printf("init cells good\n");
		if (game->tilemap[cell_y][cell_x].type == WALL)
		{
			printf("tilemap check good\n");
			ray_hit->wall_distance = i;
			break ;
		}
		printf("loop count: %i\n", i);
		i++;
	}
	return (*ray_hit);
}

void	draw_wall(t_game *game, int x, t_rayhit *x_ray)
{
	int	i;
	int	colour;
	int	wall_height;
	int	wall_position_y;
	int	wall_width;

	printf("wall distance: %f\n", x_ray->wall_distance);
	wall_height = x_ray->wall_distance * fabs(tan(FOV / 2) * 2);
	printf("wall height: %i\n", wall_height);
	wall_position_y = (WIN_HEIGHT / 2) - (wall_height / 2);
	wall_width = wall_height * 1.78;
	printf("wall width: %i\n", wall_width);
	i = wall_position_y;
	while (i < wall_position_y + wall_height)
	{	
		if (x % 44 == 0)
			colour = create_rgb(0, 0, 0);
		else
			colour = create_rgb(255, 0, 0);
		put_pixel(game->img, x, i, colour);
		i++;
	}	
}

// ray direction = player direction + camera plane x * 2*iterator 
// divided by the window width

// end = ray start + ray direction * ray length
void	raycast(t_game *game)
{
	t_rayhit	x_ray;
	int			i;
	double		ray_dir_x;
	double		ray_dir_y;
	double		ray_end_x;
	double		ray_end_y;

	x_ray.wall_colour = 0;
	x_ray.wall_distance = 0;
	x_ray.wall_normal = 0;
	x_ray.wall_texture = NULL;
	printf("in raycast\n");
	i = 0;
	while (i < WIN_WIDTH)
	{
		ray_dir_x = game->doom_guy.direction.x + game->rayban.camera_plane_x
			* (2 * i / (double)WIN_WIDTH - 1);
		ray_dir_y = game->doom_guy.direction.y + game->rayban.camera_plane_y
			* (2 * i / (double)WIN_WIDTH - 1);
		ray_end_x = game->doom_guy.direction.x + ray_dir_x
			* (game->mapdata.max_width * game->mapdata.max_height);
		ray_end_y = game->doom_guy.direction.y + ray_dir_y
			* (game->mapdata.max_width * game->mapdata.max_height);
		printf("pre cast ray\n");
		cast_ray(game, ray_dir_x, ray_dir_y, &x_ray);
		printf("post cast ray\n");
		draw_wall(game, i, &x_ray);
		printf("post draw wall\n");
		i++;
	}
}

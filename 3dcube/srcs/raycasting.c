/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:42:08 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/03 12:38:54 by tbertozz         ###   ########.fr       */
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

t_rayhit	shoot_ray(t_game *game, t_ray *ray_stuff)
{
	t_rayhit	beam;
	int			hit;
	int			beam_pos_x;
	int			beam_pos_y;
	int			step_x;
	int			step_y;

	hit = 0;
	beam_pos_x = (int)game->doom_guy.x;
	beam_pos_y = (int)game->doom_guy.y;
	if (ray_stuff->ray_dir_x < 0)
	{
		step_x = -1;
		ray_stuff->side_dist_x = (game->doom_guy.x - beam_pos_x)
			* ray_stuff->delta_dist_x;
	}
	else
	{
		step_x = 1;
		ray_stuff->side_dist_x = (beam_pos_x + 1.0 - game->doom_guy.x)
			* ray_stuff->delta_dist_x;
	}
	if (ray_stuff->ray_dir_y < 0)
	{
		step_y = -1;
		ray_stuff->side_dist_y = (game->doom_guy.y - beam_pos_y)
			* ray_stuff->delta_dist_y;
	}
	else
	{
		step_y = 1;
		ray_stuff->side_dist_y = (beam_pos_y + 1 - game->doom_guy.y)
			* ray_stuff->delta_dist_y;
	}
	while (!hit)
	{
		if (ray_stuff->side_dist_x < ray_stuff->side_dist_y)
		{
			ray_stuff->side_dist_x += ray_stuff->delta_dist_x;
			beam_pos_x += step_x;
			beam.side = 0;
		}
		else
		{
			ray_stuff->side_dist_y += ray_stuff->delta_dist_y;
			beam_pos_y += step_y;
			beam.side = 1;
		}
		if (game->tilemap[beam_pos_y][beam_pos_x].type == WALL)
			hit = 1;
	}
	if (beam.side == 0)
		beam.wall_distance = (ray_stuff->side_dist_x - ray_stuff->delta_dist_x);
	else
		beam.wall_distance = (ray_stuff->side_dist_y - ray_stuff->delta_dist_y);
	return (beam);
}

	// - y = south wall
	// + y = north wall
	// - x = west wall
	// + x = east wall
	// hit->side == 0: hit a North or South wall
	// hit->side == 1: hit a East or West wall
void	draw_wall(t_game *game, t_rayhit *hit, int x)
{
	int			i;
	int			colour;
	int			wallheight;
	int			draw_start;
	int			draw_end;

	wallheight = (int)(WIN_HEIGHT / hit->wall_distance);
	draw_start = -wallheight / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = wallheight / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	if (!(texture_picker(game, &hit)))
		print_error(3, "Error with the textures");
	
	i = draw_start;
	if (hit->side == 0)
		colour = create_rgb(255, 0, 0);
	else
		colour = create_rgb(128, 0, 0);
	while (i < draw_end)
	{
		put_pixel(game->img, x, i, colour);
		i++;
	}
}

int	texture_picker(t_game *game, t_rayhit *hit)
{
	if (hit->side == 0 && game->doom_guy.direction.y < 0)
		draw(game->mapdata.so);
	else if (hit->side == 0 && game->doom_guy.direction.y > 0)
		draw(game->mapdata.no);
	if (hit->side == 1 && game->doom_guy.direction.x < 0)
		draw(game->mapdata.we);
	else if (hit->side == 1 && game->doom_guy.direction.x > 0)
		draw(game->mapdata.ea);
}

void	raycast(t_game *game)
{
	int			ray;
	double		camera_x;
	t_ray		ray_stuff;
	t_rayhit	shotray;

	ray = 0;
	while (ray < WIN_WIDTH)
	{
		camera_x = 2 * ray / (double)WIN_WIDTH - 1;
		ray_stuff.ray_dir_x = game->doom_guy.direction.x
			+ game->doom_guy.direction.y * (camera_x / 2);
		ray_stuff.ray_dir_y = game->doom_guy.direction.y
			- game->doom_guy.direction.x * (camera_x / 2);
		ray_stuff.ray_x = game->doom_guy.direction.x + ray_stuff.ray_dir_x;
		ray_stuff.ray_y = game->doom_guy.direction.y + ray_stuff.ray_dir_y;
		if (ray_stuff.ray_dir_x == 0)
			ray_stuff.delta_dist_x = 1e30;
		else
			ray_stuff.delta_dist_x = fabs(1 / ray_stuff.ray_dir_x);
		if (ray_stuff.ray_dir_y == 0)
			ray_stuff.delta_dist_y = 1e30;
		else
			ray_stuff.delta_dist_y = fabs(1 / ray_stuff.ray_dir_y);
		shotray = shoot_ray(game, &ray_stuff);
		draw_wall(game, &shotray, ray);
		ray++;
	}
	return ;
}

int	redraw_screen(t_game *game)
{
	draw_bg(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->mlx_window,
		game->img->pointer, 0, 0);
	return (0);
}

/*
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
	wall_height = WIN_HEIGHT / x_ray->wall_distance;
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
*/

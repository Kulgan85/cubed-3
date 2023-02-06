/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:42:08 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/06 15:54:24 by tbertozz         ###   ########.fr       */
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
	{
		beam.wall_distance = (ray_stuff->side_dist_x - ray_stuff->delta_dist_x);
		beam.wall_x = beam_pos_y + beam.wall_distance * ray_stuff->ray_dir_y;
	}
	else
	{
		beam.wall_distance = (ray_stuff->side_dist_y - ray_stuff->delta_dist_y);
		beam.wall_x = beam_pos_x + beam.wall_distance * ray_stuff->ray_dir_x;
	}
	beam.wall_x -= floor(beam.wall_x);
	return (beam);
}

void	*texture_picker(t_game *game, t_rayhit *hit, t_ray *ray_stuff)
{
	void	*texture;

	texture = game->mapdata.southimg;
	printf("Hit side: %i\n", hit->side);
	printf("Wall Normal: %f\n", hit->wall_normal);
	if (hit->side == 0 && ray_stuff->ray_dir_y < 0)
	{
		texture = game->mapdata.southimg;
		printf("South\n");
	}
	else if (hit->side == 0 && ray_stuff->ray_dir_y > 0)
	{
		texture = game->mapdata.northimg;
		printf("North\n");
	}
	if (hit->side == 1 && ray_stuff->ray_dir_x < 0)
	{
		texture = game->mapdata.westimg;
		printf("West\n");
	}
	else if (hit->side == 1 && ray_stuff->ray_dir_x > 0)
	{
		texture = game->mapdata.eastimg;
		printf("Easy\n");
	}
	return (texture);
}

void	texture_wall(t_game *game, void *texture, int draw_S, int draw_E, t_rayhit *hit, int x, t_ray *ray)
{
	int		*data;
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	int		wallheight;
	double	tex_pos;
	t_images	newimg;
	int		colour;

	y = draw_S;
	tex_x = (int)(hit->wall_x * (double)(TEX_WIDTH));
	if (hit->side == 0 && ray->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (hit->side == 1 && ray->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	wallheight = (int)(WIN_HEIGHT / hit->wall_distance);
	step = 1.0 * TEX_HEIGHT / wallheight;
	tex_pos = (draw_S - WIN_HEIGHT / 2 + wallheight / 2) * step;
	data = (int *)mlx_get_data_addr(texture, &newimg.bpp, &newimg.l_size, &newimg.endian);
	while (y < draw_E)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		colour = data[TEX_HEIGHT * tex_y + tex_x];
		put_pixel(game->img, x, y, colour);
		y++;
	}


	// {
	// 	textureX = (int)(hit->wall_distance * TEX_WIDTH) % TEX_WIDTH;
	// 	textureY = (y - draw_S) * TEX_HEIGHT / WALL_HEIGHT;
	// 	colour = mlx_get_color_value(game->mlx, texture[textureY * TEX_WIDTH
	// 			+ textureX]);
	// 	printf("colour: %i\n", colour);
	// 	mlx_pixel_put(game->mlx, game->mlx_window, x, y, colour);
	// 	y++;
	// }
}

void	draw_wall(t_game *game, t_rayhit *hit, int x, t_ray *aray)
{
	// int			i;
	int			wallheight;
	int			draw_start;
	int			draw_end;
	void		*texture;

	wallheight = (int)(WIN_HEIGHT / hit->wall_distance);
	draw_start = -wallheight / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = wallheight / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	printf("Pre texture pick\n");
	texture = texture_picker(game, hit, aray);
	printf("texture success\n");
	texture_wall(game, texture, draw_start, draw_end, hit, x, aray);
	printf("Post texture wall\n");
	// i = draw_start;
	// if (hit->side == 0)
	// 	colour = create_rgb(255, 0, 0);
	// else
	// 	colour = create_rgb(128, 0, 0);
	// while (i < draw_end)
	// {
	// 	put_pixel(game->img, x, i, colour);
	// 	i++;
	// }
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->img, 0, 0);
}

// - y = south wall
// + y = north wall
// - x = west wall
// + x = east wall
// hit->side == 0: hit a North or South wall
// hit->side == 1: hit a East or West wall

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
		draw_wall(game, &shotray, ray, &ray_stuff);
		ray++;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:42:08 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/06 10:57:19 by tbertozz         ###   ########.fr       */
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

char	*texture_picker(t_game *game, t_rayhit *hit)
{
	char	*texture;

	texture = NULL;
	printf("Hit side: %i\n", hit->side);
	printf("Wall Normal: %f\n", hit->wall_normal);
	if (hit->side == 0 && game->doom_guy.direction.y < 0)
	{
		texture = game->mapdata.so;
		printf("South\n");
	}
	else if (hit->side == 0 && hit->wall_normal > 0)
	{
		texture = game->mapdata.no;
		printf("North\n");
	}
	if (hit->side == 1 && hit->wall_normal < 0)
	{
		texture = game->mapdata.we;
		printf("West\n");
	}
	else if (hit->side == 1 && game->doom_guy.direction.x > 0)
	{
		texture = game->mapdata.ea;
		printf("Easy\n");
	}
	return (texture);
}

void	texture_wall(t_game *game, char *tex_name, int draw_S, int draw_E, t_rayhit *hit, int x)
{
	int	*image;
	int	*texture;
	int	y;
	int num1;
	int num2;
	int	textureX;
	int	textureY;
	int	colour;
	int *PTR_TEX_HEIGHT;
	int	*PTR_TEX_WIDTH;

	num1 = TEX_HEIGHT;
	num2 = TEX_WIDTH;
	printf("in tex_wall\n");
	PTR_TEX_HEIGHT = NULL;
	PTR_TEX_WIDTH = NULL;
	printf("fine\n");
	PTR_TEX_HEIGHT = &num1;
	printf("Height good\n");
	PTR_TEX_WIDTH = &num2;
	printf("Height is: %i\n", *PTR_TEX_HEIGHT);
	printf("Width is: %i\n", *PTR_TEX_WIDTH);
	printf("Tex_name: %s\n", tex_name);
	image = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	texture = mlx_xpm_file_to_image(game->mlx, tex_name,
			PTR_TEX_WIDTH, PTR_TEX_HEIGHT);
	if (!texture)
		print_error(8, "Bad Texture PTR\n");
	y = draw_S;
	while (y < draw_E)
	{
		textureX = (int)(hit->wall_distance * TEX_WIDTH) % TEX_WIDTH;
		textureY = (y - draw_S) * TEX_HEIGHT / WALL_HEIGHT;
		colour = mlx_get_color_value(game->mlx, texture[textureY * TEX_WIDTH
				+ textureX]);
		mlx_pixel_put(game->mlx, game->mlx_window, x, y, colour);
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_window, image, 0, 0);
}

void	draw_wall(t_game *game, t_rayhit *hit, int x)
{
	int			i;
	int			colour;
	int			wallheight;
	int			draw_start;
	int			draw_end;
	char		*texture;

	wallheight = (int)(WIN_HEIGHT / hit->wall_distance);
	draw_start = -wallheight / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = wallheight / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	printf("Pre texture wall\n");
	texture = texture_picker(game, hit);
	printf("Texture: %s\n", texture);
	texture_wall(game, texture, draw_start, draw_end, hit, x);
	printf("Post texture wall\n");
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
		draw_wall(game, &shotray, ray);
		ray++;
	}
	return ;
}

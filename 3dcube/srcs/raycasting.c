/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:42:08 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/08 16:30:48 by jwilliam         ###   ########.fr       */
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

void	shoot_ray(t_game *game, t_ray *ray_stuff)
{
	ray_stuff->hit = 0;
	ray_stuff->beam_pos_x = (int)game->doom_guy.x;
	ray_stuff->beam_pos_y = (int)game->doom_guy.y;
	if (ray_stuff->ray_dir_x < 0)
	{
		ray_stuff->step_x = -1;
		ray_stuff->side_dist_x = (game->doom_guy.x - ray_stuff->beam_pos_x)
			* ray_stuff->delta_dist_x;
	}
	else
	{
		ray_stuff->step_x = 1;
		ray_stuff->side_dist_x = (ray_stuff->beam_pos_x + 1.0 - game->doom_guy.x)
			* ray_stuff->delta_dist_x;
	}
	if (ray_stuff->ray_dir_y < 0)
	{
		ray_stuff->step_y = -1;
		ray_stuff->side_dist_y = (game->doom_guy.y - ray_stuff->beam_pos_y)
			* ray_stuff->delta_dist_y;
	}
	else
	{
		ray_stuff->step_y = 1;
		ray_stuff->side_dist_y = (ray_stuff->beam_pos_y + 1 - game->doom_guy.y)
			* ray_stuff->delta_dist_y;
	}
	while (!ray_stuff->hit)
	{
		if (ray_stuff->side_dist_x < ray_stuff->side_dist_y)
		{
			ray_stuff->side_dist_x += ray_stuff->delta_dist_x;
			ray_stuff->beam_pos_x += ray_stuff->step_x;
			ray_stuff->side = 0;
		}
		else
		{
			ray_stuff->side_dist_y += ray_stuff->delta_dist_y;
			ray_stuff->beam_pos_y += ray_stuff->step_y;
			ray_stuff->side = 1;
		}
		if (game->tilemap[ray_stuff->beam_pos_y][ray_stuff->beam_pos_x].type == WALL)
			ray_stuff->hit = 1;
	}
	if (ray_stuff->side == 0)
	{
		ray_stuff->wall_distance = (ray_stuff->side_dist_x - ray_stuff->delta_dist_x);
		ray_stuff->wall_x = game->doom_guy.y + ray_stuff->wall_distance * ray_stuff->ray_dir_y;
	}
	else
	{
		ray_stuff->wall_distance = (ray_stuff->side_dist_y - ray_stuff->delta_dist_y);
		ray_stuff->wall_x = game->doom_guy.x + ray_stuff->wall_distance * ray_stuff->ray_dir_x;
	}
	ray_stuff->wall_x -= floor(ray_stuff->wall_x);
	return ;
}

void	*texture_picker(t_game *game, t_ray *ray_stuff)
{
	void	*texture;

	texture = NULL;
	if (ray_stuff->side == 0)
	{
		if (ray_stuff->ray_dir_x < 0)
			texture = game->mapdata.eastimg;
		else
			texture = game->mapdata.westimg;
	}
	else if (ray_stuff->side == 1)
	{
		if (ray_stuff->ray_dir_y < 0)
			texture = game->mapdata.northimg;
		else
			texture = game->mapdata.southimg;
	}
	return (texture);
}

void	texture_wall(t_game *game, int x, t_ray *ray)
{
	int		*data;
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	t_images	newimg;
	int		colour;

	y = ray->draw_start;
	tex_x = (int)(ray->wall_x * (double)(TEX_WIDTH));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	step = 1.0 * TEX_HEIGHT / ray->wallheight;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->wallheight / 2) * step;
	data = (int *)mlx_get_data_addr(ray->texture, &newimg.bpp, &newimg.l_size, &newimg.endian);
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		colour = data[TEX_HEIGHT * tex_y + tex_x];
		put_pixel(game->img, x, y, colour);
		y++;
	}
}

void	draw_wall(t_game *game, int x, t_ray *aray)
{
	aray->wallheight = (int)(WIN_HEIGHT / aray->wall_distance);
	aray->draw_start = -aray->wallheight / 2 + WIN_HEIGHT / 2;
	if (aray->draw_start < 0)
		aray->draw_start = 0;
	aray->draw_end = aray->wallheight / 2 + WIN_HEIGHT / 2;
	if (aray->draw_end >= WIN_HEIGHT)
		aray->draw_end = WIN_HEIGHT - 1;
	aray->texture = texture_picker(game, aray);
	texture_wall(game, x, aray);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->img, 0, 0);
}

void	raycast(t_game *game)
{
	int			ray;
	t_ray		ray_stuff;
//	t_rayhit	shotray;

	ray = 0;
	while (ray < WIN_WIDTH)
	{
		ray_stuff.camera_x = 2 * ray / (double)WIN_WIDTH - 1;
		// ray_stuff.ray_dir_x = game->doom_guy.direction.x + (game->doom_guy.plane_x * ray_stuff.camera_x);
		// ray_stuff.ray_dir_y = game->doom_guy.direction.y + (game->doom_guy.plane_y * ray_stuff.camera_x);
		ray_stuff.ray_dir_x = game->doom_guy.direction.x
			- game->doom_guy.direction.y * (ray_stuff.camera_x / 2);
		ray_stuff.ray_dir_y = game->doom_guy.direction.y
			+ game->doom_guy.direction.x * (ray_stuff.camera_x / 2);
	//	ray_stuff.ray_x = game->doom_guy.direction.x + ray_stuff.ray_dir_x;
	//	ray_stuff.ray_y = game->doom_guy.direction.y + ray_stuff.ray_dir_y;
		if (ray_stuff.ray_dir_x == 0)
			ray_stuff.delta_dist_x = 1e30;
		else
			ray_stuff.delta_dist_x = fabs(1 / ray_stuff.ray_dir_x);
		if (ray_stuff.ray_dir_y == 0)
			ray_stuff.delta_dist_y = 1e30;
		else
			ray_stuff.delta_dist_y = fabs(1 / ray_stuff.ray_dir_y);
		shoot_ray(game, &ray_stuff);
		draw_wall(game, ray, &ray_stuff);
		ray++;
	}
	return ;
}

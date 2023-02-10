/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:42:08 by tbertozz          #+#    #+#             */
/*   Updated: 2023/02/10 12:45:31 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_walls(t_game *game, t_ray *ray_stuff)
{
	if (ray_stuff->side == 0)
	{
		ray_stuff->wall_distance = (ray_stuff->side_dist_x
				- ray_stuff->delta_dist_x);
		ray_stuff->wall_x = game->doom_guy.y + ray_stuff->wall_distance
			* ray_stuff->ray_dir_y;
	}
	else
	{
		ray_stuff->wall_distance = (ray_stuff->side_dist_y
				- ray_stuff->delta_dist_y);
		ray_stuff->wall_x = game->doom_guy.x + ray_stuff->wall_distance
			* ray_stuff->ray_dir_x;
	}
	ray_stuff->wall_x -= floor(ray_stuff->wall_x);
}

void	set_ray_direction(t_game *game, t_ray *ray_stuff)
{
	if (ray_stuff->ray_dir_x < 0)
	{
		ray_stuff->step_x = -1;
		ray_stuff->side_dist_x = (game->doom_guy.x - ray_stuff->beam_pos_x)
			* ray_stuff->delta_dist_x;
	}
	else
	{
		ray_stuff->step_x = 1;
		ray_stuff->side_dist_x = (ray_stuff->beam_pos_x + 1.0
				- game->doom_guy.x) * ray_stuff->delta_dist_x;
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
}

void	shoot_ray(t_game *game, t_ray *ray_stuff)
{
	ray_stuff->hit = 0;
	ray_stuff->beam_pos_x = (int)game->doom_guy.x;
	ray_stuff->beam_pos_y = (int)game->doom_guy.y;
	set_ray_direction(game, ray_stuff);
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
		if (game->tilemap[ray_stuff->beam_pos_y][ray_stuff->beam_pos_x].type
			== WALL)
			ray_stuff->hit = 1;
	}
	return ;
}

void	set_raycast_initial(t_game *game, int ray, t_ray *ray_stuff)
{
	ray_stuff->camera_x = (2 * ray / (double)WIN_WIDTH - 1) * 1.60;
	ray_stuff->ray_dir_x = game->doom_guy.direction.x
		- game->doom_guy.direction.y * (ray_stuff->camera_x / 2);
	ray_stuff->ray_dir_y = game->doom_guy.direction.y
		+ game->doom_guy.direction.x * (ray_stuff->camera_x / 2);
	if (ray_stuff->ray_dir_x == 0)
		ray_stuff->delta_dist_x = 1e30;
	else
		ray_stuff->delta_dist_x = fabs(1 / ray_stuff->ray_dir_x);
	if (ray_stuff->ray_dir_y == 0)
		ray_stuff->delta_dist_y = 1e30;
	else
		ray_stuff->delta_dist_y = fabs(1 / ray_stuff->ray_dir_y);
}

void	raycast(t_game *game)
{
	int			ray;
	t_ray		ray_stuff;

	ray = 0;
	while (ray < WIN_WIDTH)
	{
		set_raycast_initial(game, ray, &ray_stuff);
		shoot_ray(game, &ray_stuff);
		set_walls(game, &ray_stuff);
		draw_wall(game, ray, &ray_stuff);
		ray++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_window, &game->img, 0, 0);
	return ;
}

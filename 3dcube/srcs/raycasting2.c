/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:50:39 by jwilliam          #+#    #+#             */
/*   Updated: 2023/02/10 12:45:43 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_wall(t_game *game, int x, t_ray *ray)
{
	int			*imgdata;
	int			y;
	double		step;
	t_images	newimg;
	int			colour;

	y = ray->draw_start;
	ray->tex_x = (int)(ray->wall_x * (double)(TEX_WIDTH));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	step = 1.0 * TEX_HEIGHT / ray->wallheight;
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->wallheight / 2) * step;
	imgdata = (int *)mlx_get_data_addr(ray->texture,
			&newimg.bpp, &newimg.l_size, &newimg.endian);
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos;
		ray->tex_pos += step;
		colour = imgdata[TEX_HEIGHT * ray->tex_y + ray->tex_x];
		put_pixel(&game->img, x, y, colour);
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
}

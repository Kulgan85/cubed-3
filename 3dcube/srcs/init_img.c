/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:47:42 by tbertozz          #+#    #+#             */
/*   Updated: 2023/01/24 12:56:22 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_image(t_game *game)
{
	printf("in init\n");
	game->img = (t_images *)malloc(sizeof (t_images));
	game->img->width = WIN_WIDTH;
	game->img->height = WIN_HEIGHT;
	game->img->pointer = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	printf("fine\n");
	game->img->address = mlx_get_data_addr(game->img->pointer,
			&game->img->bpp, &game->img->l_size, &game->img->endian);
	printf("I'm really not\n");
	return (1);
}

/* 
	Returns a t_color struct
t_color	new_color(int r, int g, int b, int a)
{
	t_color	color;

	color.r = (char)r;
	color.g = (char)g;
	color.b = (char)b;
	color.a = (char)a;
	return (color);
}

	Set all pixels in <panel> to <color>
void	color_panel(t_panel *panel, t_color color)
{
	int	x;
	int	y;

	panel->pixels = mlx_get_data_addr(panel->pointer, &panel->bpp,
			&panel->line_size, &panel->endian);
	y = 0;
	while (y < panel->size.y)
	{
		x = 0;
		while (x < panel->size.x)
		{
			panel->pixels[(x * 4 + panel->line_size * y) + 0] = color.b;
			panel->pixels[(x * 4 + panel->line_size * y) + 1] = color.g;
			panel->pixels[(x * 4 + panel->line_size * y) + 2] = color.r;
			panel->pixels[(x * 4 + panel->line_size * y) + 3] = color.a;
			x += 1;
		}
		y += 1;
	}
}

	Returns a colred image of the same size as the window
void	*new_panel(t_game *game, t_color color)
{
	t_panel	panel;

	panel.pointer = mlx_new_image(game->mlx,
			WIN_WIDTH, WIN_HEIGHT);
	panel.size.x = WIN_WIDTH;
	panel.size.y = WIN_HEIGHT;
	color_panel(&panel, color);
	return (panel.pointer);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:12:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/06/30 17:05:37 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "pixel_put.h"
#include <math.h>

void	draw_line(t_game *g, t_point start, t_point end, int color);

void	draw_player(t_game *g)
{
	int		x;
	int		y;
	int		a;
	int		b;
	t_point	end;
	t_point start;

	x = -1;
	while (++x < MMS)
	{
		y = -1;
		while (++y < MMS)
		{
			a = x - MMS / 4;
			b = y - MMS / 4;
			if (sqrt((a * a) + (b * b)) < MMS / 4)
			{
				my_mlx_pixel_put(&g->img,
					g->player_pos.x * MMS + x - MMS / 4,
					g->player_pos.y * MMS + y - MMS / 4,
					0x00ffff00);
			}
		}
	}
	start.x = (int)(g->player_pos.x * MMS);
	start.y = (int)(g->player_pos.y * MMS);
	end.x = start.x - 1 * MMS;
	end.y = start.y + 0 * MMS + 20;
	draw_line(g, start, end, 0x00ff00ff);
}

void	draw_square(t_coord c, int color, t_game *g)
{
	int	x;
	int	y;

	x = -1;
	while (++x < MMS)
	{
		y = -1;
		while (++y < MMS)
		{
			my_mlx_pixel_put(&g->img, c.x * MMS + x, c.y * MMS + y, color);
		}
	}
}

void	draw_minimap(t_game *g)
{
	int		x;
	int		y;
	t_coord	c;

	x = -1;
	while (++x < g->map_width)
	{
		y = -1;
		while (++y < g->map_height)
		{
			c.x = x;
			c.y = y;
			if (g->map[x + y * g->map_width] == '1')
				draw_square(c, 0x4400ff00, g);
			if (g->map[x + y * g->map_width] == '0')
				draw_square(c, 0x44ff0000, g);
			if (g->map[x + y * g->map_width] == 'N')
				draw_square(c, 0x440000ff, g);
		}
	}
	g->player_pos.x = 3.5;
	g->player_pos.y = 1.25;
	draw_player(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

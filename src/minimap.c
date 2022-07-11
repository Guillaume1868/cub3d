/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:12:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/11 10:18:15 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "pixel_put.h"
#include "draw_line.h"
#include <math.h>

void	draw_player(t_game *g)
{
	t_vars2	v;

	v.x = -1;
	while (++v.x < MMS)
	{
		v.y = -1;
		while (++v.y < MMS)
		{
			v.a = v.x - MMS / 4;
			v.b = v.y - MMS / 4;
			if (sqrt((v.a * v.a) + (v.b * v.b)) < MMS / 4)
			{
				my_mlx_pixel_put(&g->img,
					g->player_pos.x * MMS + v.x - MMS / 4,
					g->player_pos.y * MMS + v.y - MMS / 4,
					0x00ffff00);
			}
		}
	}
	v.start.x = (int)(g->player_pos.x * MMS);
	v.start.y = (int)(g->player_pos.y * MMS);
	v.end.x = v.start.x - 1 * MMS;
	v.end.y = v.start.y + 0 * MMS + 20;
	draw_line(g, v.start, v.end, 0x00ff00ff);
}

void	draw_square(t_coord c, int color, t_game *g)
{
	int	x;
	int	y;
	int	dc;
	int	wdth;

	x = -1;
	wdth = MMS / 25;
	if (wdth < 1)
		wdth = 1;
	while (++x < MMS)
	{
		y = -1;
		while (++y < MMS)
		{
			if (((x < wdth) || (y < wdth))
				|| ((MMS - x < wdth) || (MMS - y < wdth)))
				dc = 0x0042424242;
			else
				dc = color;
			my_mlx_pixel_put(&g->img, c.x * MMS + x, c.y * MMS + y, dc);
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
	g->player_pos.y = 2.25;
	draw_player(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

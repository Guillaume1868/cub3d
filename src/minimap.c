/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:12:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/18 18:24:42 by gaubert          ###   ########.fr       */
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
			v.a = v.x - MMS / 5;
			v.b = v.y - MMS / 5;
			if (sqrt((v.a * v.a) + (v.b * v.b)) < MMS / 5)
			{
				my_mlx_pixel_put(&g->img,
					g->p.x * MMS + v.x - MMS / 5,
					g->p.y * MMS + v.y - MMS / 5,
					0x00ffff00);
			}
		}
	}
	v.start.x = (int)(g->p.x * MMS);
	v.start.y = (int)(g->p.y * MMS);
	v.end.x = (g->p.x * MMS) + (g->p.dx) * MMS ;
	v.end.y = (g->p.y * MMS) + (g->p.dy) * MMS ;
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
				dc = 0x00424242;
			else
				dc = color;
			my_mlx_pixel_put(&g->img, c.x * MMS + x, c.y * MMS + y, dc);
		}
	}
}

void	clear_image(t_game *g, int x, int y);

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
				draw_square(c, 0x0000ff00, g);
			if (g->map[x + y * g->map_width] == '0')
				draw_square(c, 0x00ff0000, g);
			if (g->map[x + y * g->map_width] == 'N')
				draw_square(c, 0x000000ff, g);
		}
	}
	draw_player(g);
	ray_cast(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win2, g->img2.img, 0, 0);
	clear_image(g, 1920, 1080);
}

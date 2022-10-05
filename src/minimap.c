/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:12:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/04 12:23:47 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "utils.h"
#include "minimap.h"
#include "pixel_put.h"
#include "draw_line.h"
#include "threed.h"
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
			if (g->map->map[x + y * g->map_width] == '1')
				draw_square(c, 0x0000ff00, g);
			if (g->map->map[x + y * g->map_width] == '0')
				draw_square(c, 0x00ff0000, g);
			if (g->map->map[x + y * g->map_width] == 'N')
				draw_square(c, 0x000000ff, g);
		}
	}
	draw_player(g);
}

void	put_ray_to_win(t_game *g)
{
	int	column;
	int	color;

	color = 0;
	column = 0;
	while (++column < 1920)
	{
		if (g->rays[column].hit == 'S')
			color = 0x00ff0000;
		else if (g->rays[column].hit == 'N')
			color = 0x0000ff00;
		else if (g->rays[column].hit == 'W')
			color = 0x000000ff;
		else
			color = 0x0000ffff;
		draw_column(g, &g->rays[column], column);
		draw_map_ray(g, &g->rays[column], color);
	}
}

void	draw_rays(t_game *g)
{
	anti_bad(g->rays);
	put_ray_to_win(g);
}

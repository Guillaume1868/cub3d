/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:12:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/15 15:10:13 by gaubert          ###   ########.fr       */
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

void	while_dof(t_game *g, t_rvars *v)
{
	while (v->dof < 8)
	{
		v->mx = (int)(v->rx);
		v->my = (int)(v->ry);
		v->mp = v->my * g->map_width + v->mx;
		if (v->mp > 0 && v->mp < g->map_width * g->map_height
			&& g->map[v->mp] == '1')
			v->dof = 8;
		else
		{
			v->rx += v->xo;
			v->ry += v->yo;
			v->dof += 1;
		}
	}
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}

void	ray_cast(t_game *g)
{
	t_rvars	v;

	v.ra = g->p.angle;
	v.r = -1;
	while (++v.r < 1)
	{
		//horizontal lines
		v.dof = 0;
		v.atan = -1 / tan(v.ra);
		if (v.ra > PI) //looking up
		{
			v.ry = (int) g->p.y - 0.0001;
			v.rx = (g->p.y - v.ry) * v.atan + g->p.x;
			v.yo = -1;
			v.xo = -v.yo * v.atan;
		}
		if (v.ra < PI && v.ra != 0) //looking down
		{
			v.ry = (int) g->p.y + 1;
			v.rx = (g->p.y - v.ry) * v.atan + g->p.x;
			v.yo = 1;
			v.xo = -v.yo * v.atan;
		}
		if (v.ra == 0 || v.ra == PI)
		{
			v.rx = g->p.x;
			v.ry = g->p.y;
			v.dof = 8;
		}
		while_dof(g, &v);
		v.hx = v.rx;
		v.hy = v.ry;
		v.disH = dist(g->p.x, g->p.y, v.hx, v.hy);
		//vertical lines
		v.dof = 0;
		v.atan = -tan(v.ra);
		if (v.ra > PI / 2 && v.ra < 3 * PI / 2) //looking left
		{
			v.rx = (int) g->p.x - 0.0001;
			v.ry = (g->p.x - v.rx) * v.atan + g->p.y;
			v.xo = -1;
			v.yo = -v.xo * v.atan;
		}
		if (v.ra < PI / 2 || v.ra > 3 * PI / 2) //looking right
		{
			v.rx = (int) g->p.x + 1;
			v.ry = (g->p.x - v.rx) * v.atan + g->p.y;
			v.xo = 1;
			v.yo = -v.xo * v.atan;
		}
		if (v.ra == PI / 2 || v.ra == 4.71238899f)
		{
			v.rx = g->p.x;
			v.ry = g->p.y;
			v.dof = 8;
			printf("FUCK\n");
		}
		while_dof(g, &v);
		v.vx = v.rx;
		v.vy = v.ry;
		v.disV = dist(g->p.x, g->p.y, v.vx, v.vy);
		if (v.ra == PI / 2 || v.ra == 4.71238899f)
			v.disV = 1000000;
		printf("disH:%f disV:%f vx:%f vy:%f hx:%f hy:%f px:%f py:%f \n", v.disH, v.disV, v.vx, v.vy, v.hx, v.hy, g->p.dx, g->p.dy);
		if (v.disV < v.disH)
			draw_map_ray(g, &v, 0x00ffaa00);
		else
		{
			v.rx = v.hx;
			v.ry = v.hy;
			draw_map_ray(g, &v, 0x0000aaff);
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
				draw_square(c, 0x0000ff00, g);
			if (g->map[x + y * g->map_width] == '0')
				draw_square(c, 0x00ff0000, g);
			if (g->map[x + y * g->map_width] == 'N')
				draw_square(c, 0x000000ff, g);
		}
	}
	draw_player(g);
	ray_cast(g);
	printf("pa: %f\n", g->p.angle);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

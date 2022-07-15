/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:19:05 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/15 14:34:32 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "pixel_put.h"
#include "draw_line.h"

//Bresenham's line algorithm

void	draw_line2(t_vars *v, t_point o, t_point i, int color)
{
	while (1)
	{
		if ((o.x < SCREEN_WIDTH) && (o.y < SCREEN_HEIGHT) && ! (o.x < 0
				|| o.y < 0))
			my_mlx_pixel_put(&v->g->img, o.x, o.y, color);
		//else
			//printf("Segfault prevented : drawing pixel outside of img !\n");
		if (o.x == i.x && o.y == i.y)
			break ;
		v->e2 = 2 * v->error;
		if (v->e2 >= v->dy)
		{
			if (o.x == i.x)
				break ;
			v->error = v->error + v->dy;
			o.x = o.x + v->sx;
		}
		if (v->e2 <= v->dx)
		{
			if (o.y == i.y)
				break ;
			v->error = v->error + v->dx;
			o.y = o.y + v->sy;
		}
	}
}

void	draw_line(t_game *g, t_point o, t_point i, int color)
{
	t_vars	v;

	v.dx = abs(i.x - o.x);
	if (o.x < i.x)
		v.sx = 1;
	else
		v.sx = -1;
	v.dy = -abs(i.y - o.y);
	if (o.y < i.y)
		v.sy = 1;
	else
		v.sy = -1;
	v.error = v.dx + v.dy;
	v.g = g;
	draw_line2(&v, o, i, color);
}

//Other lines utils
void	draw_map_ray(t_game *g, t_rvars *v, int color)
{
	v->s.x = g->p.x * MMS;
	v->s.y = g->p.y * MMS;
	v->e.x = v->rx * MMS;
	v->e.y = v->ry * MMS;
	//printf("sx:%d sy:%d ex:%d ey:%d", v->s.x, v->s.y, v->e.x, v->e.y);
	fflush(stdout);
	draw_line(g, v->s, v->e, color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:19:05 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/01 15:41:44 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "pixel_put.h"
#include "draw_line.h"

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
	while (1)
	{
		my_mlx_pixel_put(&g->img, o.x, o.y, color);
		if (o.x == i.x && o.y == i.y)
			break ;
		v.e2 = 2 * v.error;
		if (v.e2 >= v.dy)
		{
			if (o.x == i.x)
				break ;
			v.error = v.error + v.dy;
			o.x = o.x + v.sx;
		}
		if (v.e2 <= v.dx)
		{
			if (o.y == i.y)
				break ;
			v.error = v.error + v.dx;
			o.y = o.y + v.sy;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:19:05 by gaubert           #+#    #+#             */
/*   Updated: 2022/06/30 16:46:44 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "pixel_put.h"

void	plot_line_low(t_game *g, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	d;
	int	y;
	int	x;
	int yi;

	dx = end.x - start.x;
	dy = end.y - start.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	y = start.y;
	x = start.x - 1;
	while (++x <= end.x)
	{
		my_mlx_pixel_put(&g->img, x, y, color);
		if (d > 0)
		{
			y = y + yi;
			d = d + (2 * (dy - dx));
		}
		d = d + 2 * dy;
	}
}

void	plot_line_high(t_game *g, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	d;
	int	y;
	int	x;
	int xi;

	dx = end.x - start.x;
	dy = end.y - start.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = start.x;
	y = start.y - 1;
	while (++y <= end.y)
	{
		my_mlx_pixel_put(&g->img, x, y, color);
		if (d > 0)
		{
			x = x + xi;
			d = d + (2 * (dx - dy));
		}
		d = d + 2 * dx;
	}
}

void	draw_line(t_game *g, t_point start, t_point end, int color)
{
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			plot_line_low(g, end, start, color);
		else
			plot_line_low(g, start, end, color);
	}
	else
	{
		if (start.y > end.y)
			plot_line_high(g, end, start, color);
		else
			plot_line_high(g, start, end, color);
	}
}

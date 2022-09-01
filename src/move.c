/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:28:59 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/01 11:57:20 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include <math.h>

void	move(t_game *g, int i)
{
	float	x;
	float	y;

	x = 0;
	y = 0;
	if (i == 1)
	{
		x = g->p.x + g->p.dx;
		y = g->p.y + g->p.dy;
	}
	else if (i == -1)
	{
		x = g->p.x - g->p.dx;
		y = g->p.y - g->p.dy;
	}
	if (x < 0 || y < 0)
		return ;
	if (x >= g->map_width || y >= g->map_height)
		return ;
	if (g->map->map[(int) x + (int) y * g->map_width] == '1')
		return ;
	g->p.x = x;
	g->p.y = y;
}

int	key_hook(int keycode, t_game *g)
{
	if (keycode == 13 && g->state == playing)
		move(g, 1);
	else if (keycode == 0 && g->state == playing)
	{
		g->p.angle -= 2 * PI / 20;
		if (g->p.angle < 0)
			g->p.angle += 2 * PI;
		g->p.dx = cos(g->p.angle) / 5;
		g->p.dy = sin(g->p.angle) / 5;
	}
	else if (keycode == 1 && g->state == playing)
		move(g, -1);
	else if (keycode == 2 && g->state == playing)
	{
		g->p.angle += 2 * PI / 20;
		if (g->p.angle > 2 * PI)
			g->p.angle -= 2 * PI;
		g->p.dx = cos(g->p.angle) / 5;
		g->p.dy = sin(g->p.angle) / 5;
	}
	else if (keycode == 53)
		clean(NULL, g);
	draw_minimap(g);
	return (0);
}

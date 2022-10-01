/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:28:59 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/01 13:37:12 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include <math.h>
#include "draw_all.h"
#include "keys.h"
#include "raycast.h"

int	check_wall(t_game *g, int i)
{
	t_rvars	v;

	v.ra = g->p.angle;
	if (i == -1)
	{
		v.ra += PI;
		if (v.ra > 2 * PI)
			v.ra -= 2 * PI;
	}
	horizontal_rays(&v, g);
	vertical_rays(&v, g);
	if (v.disv < 0.2 || v.dish < 0.2)
		return (1);
	return (0);
}

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
	if (check_wall(g, i))
		return ;
	g->p.x = x;
	g->p.y = y;
}

void	rotate(t_game *g, float angle)
{
	g->p.angle += angle;
	if (g->p.angle < 0)
		g->p.angle += 2 * PI;
	if (g->p.angle > 2 * PI)
		g->p.angle -= 2 * PI;
	g->p.dx = cos(g->p.angle) / 5;
	g->p.dy = sin(g->p.angle) / 5;
}

int	key_hook(int keycode, t_game *g)
{
	if (keycode == K_W)
		move(g, 1);
	else if (keycode == K_LEFT_ARROW)
		rotate(g, -2 * PI / 20);
	else if (keycode == K_S)
		move(g, -1);
	else if (keycode == K_RIGHT_ARROW)
		rotate(g, 2 * PI / 20);
	else if (keycode == K_A)
	{
		rotate(g, -2 * PI / 4);
		move(g, 1);
		rotate(g, 2 * PI / 4);
	}
	else if (keycode == K_D)
	{
		rotate(g, 2 * PI / 4);
		move(g, 1);
		rotate(g, -2 * PI / 4);
	}
	else if (keycode == K_ESC)
		clean(g);
	draw_all(g);
	return (0);
}

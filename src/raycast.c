/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:38:55 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/26 13:48:00 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "draw_line.h"
#include "utils.h"
#include <math.h>

void	vertical_rays2(t_rvars *v, t_game *g)
{
	if (v->ra > PI / 2 && v->ra < 3 * PI / 2)
	{
		v->rx = (int) g->p.x - 0.0001;
		v->ry = (g->p.x - v->rx) * v->atan + g->p.y;
		v->xo = -1;
		v->yo = -v->xo * v->atan;
	}
	if (v->ra < PI / 2 || v->ra > 3 * PI / 2)
	{
		v->rx = (int) g->p.x + 1;
		v->ry = (g->p.x - v->rx) * v->atan + g->p.y;
		v->xo = 1;
		v->yo = -v->xo * v->atan;
	}
	if (v->ra == PI / 2 || v->ra == 4.71238899f)
	{
		v->rx = g->p.x;
		v->ry = g->p.y;
		v->dof = 8;
	}
}

void	vertical_rays(t_rvars *v, t_game *g)
{
	v->dof = 0;
	v->atan = -tan(v->ra);
	vertical_rays2(v, g);
	while_dof(g, v, 1);
	v->vx = v->rx;
	v->vy = v->ry;
	v->disv = dist(g->p.x, g->p.y, v->vx, v->vy);
	if (v->ra == PI / 2 || v->ra == 4.71238899f)
		v->disv = 1000000;
	v->dist = v->disv;
}

void	horizontal_rays2(t_rvars *v, t_game *g)
{
	if (v->ra > PI)
	{
		v->ry = (int) g->p.y - 0.0001;
		v->rx = (g->p.y - v->ry) * v->atan + g->p.x;
		v->yo = -1;
		v->xo = -v->yo * v->atan;
	}
	if (v->ra < PI && v->ra != 0)
	{
		v->ry = (int) g->p.y + 1;
		v->rx = (g->p.y - v->ry) * v->atan + g->p.x;
		v->yo = 1;
		v->xo = -v->yo * v->atan;
	}
	if (v->ra == 0 || v->ra == PI)
	{
		v->rx = g->p.x;
		v->ry = g->p.y;
		v->dof = 8;
	}
}

void	horizontal_rays(t_rvars *v, t_game *g)
{
	v->dof = 0;
	v->atan = -1 / tan(v->ra);
	horizontal_rays2(v, g);
	while_dof(g, v, 0);
	v->hx = v->rx;
	v->hy = v->ry;
	v->dish = dist(g->p.x, g->p.y, v->hx, v->hy);
}

void	ray_cast(t_game *g)
{
	t_rvars	v;

	v.ra = g->p.angle - DR * 960;
	v.r = -1;
	while (++v.r < 1920)
	{
		if (v.ra < 0)
			v.ra += 2 * PI;
		if (v.ra > 2 * PI)
			v.ra -= 2 * PI;
		horizontal_rays(&v, g);
		vertical_rays(&v, g);
		if (!(v.disv < v.dish))
		{
			v.rx = v.hx;
			v.ry = v.hy;
			v.dist = v.dish;
			v.hit = v.hith;
		}
		else
			v.hit = v.hitv;
		store_ray(g, &v);
		v.ra += DR;
	}
}
